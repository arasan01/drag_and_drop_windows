import 'dart:async';
import 'package:flutter/services.dart';

class DragAndDropWindows {
  static const EventChannel _eventChannel =
      EventChannel('drag_and_drop_windows');

  static final Stream<List<String>> _dragEventStream = _eventChannel
      .receiveBroadcastStream()
      .map((event) => List<String>.from(event))
      .asBroadcastStream();

  static Stream<List<String>> get dragEventStream => _dragEventStream;
}
