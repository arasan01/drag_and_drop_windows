import 'dart:async';
import 'package:flutter/services.dart';

const EventChannel _eventChannel = EventChannel('drag_and_drop_windows');

final Stream<List<String>> _dropEventStream = _eventChannel
    .receiveBroadcastStream()
    .map((event) => List<String>.from(event))
    .asBroadcastStream();

/// Listen the drop event at [path]
///
/// This Stream will never send out an Error. It will always return data.
/// This Stream will always receive events from when the application
/// is started until it is terminated.
Stream<List<String>> get dropEventStream => _dropEventStream;
