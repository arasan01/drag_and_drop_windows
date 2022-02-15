# drag_and_drop_windows

A Flutter plugin that adds drag-and-drop functionality for windows.

![](https://github.com/arasan01/drag_and_drop_windows/blob/main/.github/preview.gif)

_Example app running on Microsoft Windows 11 (Debug)_

## Installation

```yaml
dependencies:
  drag_and_drop_windows: ^0.0.1
```

or

```shell
$ flutter pub add drag_and_drop_windows
```

Subscribe to the drop event stream.

```dart
import 'package:drag_and_drop_windows/drag_and_drop_windows.dart';
StreamSubscription subscription = dropEventStream.listen((paths) {
  // something to do
});
```

## API

This plugin provides only one event stream.

- `dropEventStream` (`Stream<List<String>>`) Send the item's path, one or more, that was dragged into the app window.
