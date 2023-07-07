#include "include/drag_and_drop_windows/drag_and_drop_windows_plugin.h"

// This must be included before many other Windows headers.
#include <windows.h>

// For getPlatformVersion; remove unless needed for your plugin implementation.
#include <VersionHelpers.h>

#include <flutter/plugin_registrar_windows.h>
#include <flutter/standard_method_codec.h>
#include <flutter/binary_messenger.h>
#include <flutter/event_channel.h>
#include <flutter/event_sink.h>
#include <flutter/event_stream_handler.h>
#include <flutter/event_stream_handler_functions.h>

#include <map>
#include <memory>
#include <sstream>

auto const kDragAndDropWindowsChannelName = "drag_and_drop_windows";

namespace {

class DragAndDropWindowsPlugin : public flutter::Plugin {
  public:
    static void RegisterWithRegistrar(flutter::PluginRegistrarWindows *registrar);

  DragAndDropWindowsPlugin(flutter::BinaryMessenger* messenger);

  private:
    std::optional<LRESULT> MessageHandler(HWND window, UINT const message, WPARAM const wparam, LPARAM const lparam) noexcept;
    std::unique_ptr<flutter::EventSink<flutter::EncodableValue>> event_sink_;
    std::unique_ptr<flutter::EventChannel<flutter::EncodableValue>> event_channel_;
};

// static
void DragAndDropWindowsPlugin::RegisterWithRegistrar(
    flutter::PluginRegistrarWindows *registrar) {
  auto plugin = std::make_unique<DragAndDropWindowsPlugin>(registrar->messenger());
  flutter::WindowProcDelegate delegate([plugin_pointer = plugin.get()](HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) {
    return plugin_pointer->MessageHandler(hwnd, message, wparam, lparam);
  });

  registrar->RegisterTopLevelWindowProcDelegate(delegate);
  registrar->AddPlugin(std::move(plugin));
}

DragAndDropWindowsPlugin::DragAndDropWindowsPlugin(flutter::BinaryMessenger* messenger) {
  event_channel_ = std::make_unique<flutter::EventChannel<flutter::EncodableValue>>(
      messenger,
      kDragAndDropWindowsChannelName,
      &flutter::StandardMethodCodec::GetInstance());
  auto handler = std::make_unique<flutter::StreamHandlerFunctions<flutter::EncodableValue>>(
      [this](
        const flutter::EncodableValue* arguments,
        std::unique_ptr<flutter::EventSink<flutter::EncodableValue>>&& events) {
        // onListen
        event_sink_ = std::move(events);
        return nullptr;
        },
      [this](const flutter::EncodableValue* arguments) {
        // onCancel
        event_sink_ = nullptr;
        return nullptr;
      }
  );
  event_channel_->SetStreamHandler(std::move(handler));
}

std::optional<LRESULT> DragAndDropWindowsPlugin::MessageHandler(HWND window, UINT const message, WPARAM const wparam, LPARAM const lparam) noexcept {
  std::optional<LRESULT> result;
  switch (message) {
    case WM_ACTIVATEAPP: {
      DragAcceptFiles(window, true);
      return 0;
    }
    case WM_DROPFILES: {
      HDROP hdrop = reinterpret_cast<HDROP>(wparam);
      UINT file_count = DragQueryFileW(hdrop, 0xFFFFFFFF, nullptr, 0);
      if (file_count == 0) {
        return 0;
      }
      flutter::EncodableList files;
      for (UINT i = 0; i < file_count; ++i) {
        wchar_t filename[MAX_PATH];
        if (DragQueryFileW(hdrop, i, filename, MAX_PATH)) {
          int iBufferSize = ::WideCharToMultiByte(CP_UTF8, 0, filename, -1, NULL, 0, NULL, NULL);
          char* cpBufUTF8 = new char[iBufferSize];
          ::WideCharToMultiByte(CP_UTF8, 0, filename, -1, cpBufUTF8, iBufferSize, NULL, NULL);
          std::string s(cpBufUTF8, cpBufUTF8 + iBufferSize - 1);
          delete[] cpBufUTF8;
          flutter::EncodableValue file(std::move(s));
          files.push_back(std::move(file));
        }
      }
      DragFinish(hdrop);
      if (event_sink_) event_sink_->Success(files);
      return 0;
    }
  }
  return std::nullopt;
}

}  // namespace

void DragAndDropWindowsPluginRegisterWithRegistrar(
  FlutterDesktopPluginRegistrarRef registrar) {
  DragAndDropWindowsPlugin::RegisterWithRegistrar(
      flutter::PluginRegistrarManager::GetInstance()
          ->GetRegistrar<flutter::PluginRegistrarWindows>(registrar));
}
