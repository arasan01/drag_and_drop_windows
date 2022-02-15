import 'dart:async';
import 'package:flutter/material.dart';
import 'package:drag_and_drop_windows/drag_and_drop_windows.dart' as dd;

void main() {
  runApp(const MyApp());
}

class MyApp extends StatefulWidget {
  const MyApp({Key? key}) : super(key: key);

  @override
  State<MyApp> createState() => _MyAppState();
}

class _MyAppState extends State<MyApp> {
  String _paths = 'Not received yet';
  StreamSubscription? _subscription;

  @override
  void initState() {
    super.initState();
    _subscription ??= dd.dropEventStream.listen((paths) {
      setState(() {
        _paths = paths.join('\n');
      });
    });
  }

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: Scaffold(
        appBar: AppBar(
          title: const Text('Plugin example app'),
        ),
        body: Center(
          child: Column(
            children: [
              ElevatedButton(
                  onPressed: () {
                    setState(() {
                      _paths = 'aa';
                    });
                  },
                  child: const Text('Refresh')),
              Text('Received paths:\n$_paths\n'),
            ],
          ),
        ),
      ),
    );
  }
}
