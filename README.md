# drag_and_drop_windows

A Flutter plugin that adds drag-and-drop functionality for windows.

## Now Trouble

After the app window reads the path of the dragged item, it outputs sigterm to stop the app from stopping when it tries to return a value using `event_sink_`.
My guess is that it's failing around NotImplement, such as EventSink not being implemented because it's not FlutterEngine when it receives a messenger as a plugin, and that PluginRegistrar can't access apps such as EventSink.

## Dig source code

Main C++ Code:
```
windows/include/drag_and_drop_windows/drag_and_drop_windows_plugin.h
windows/drag_and_drop_windows_plugin.cpp
```

Main Dart Code:
```
lib/src/drag_and_drop_event.dart
```

