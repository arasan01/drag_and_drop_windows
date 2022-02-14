# drag_and_drop_windows

A new flutter plugin project.

## Now Trouble

After the app window reads the path of the dragged item, it outputs sigterm to stop the app from stopping when it tries to return a value using `event_sink_`.
My guess is that it's failing around NotImplement, such as EventSink not being implemented because it's not FlutterEngine when it receives a messenger as a plugin, and that PluginRegistrar can't access apps such as EventSink.

## Getting Started

This project is a starting point for a Flutter
[plug-in package](https://flutter.dev/developing-packages/),
a specialized package that includes platform-specific implementation code for
Android and/or iOS.

For help getting started with Flutter, view our
[online documentation](https://flutter.dev/docs), which offers tutorials,
samples, guidance on mobile development, and a full API reference.

