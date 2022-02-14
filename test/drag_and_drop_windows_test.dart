import 'package:flutter/services.dart';
import 'package:flutter_test/flutter_test.dart';

void main() {
  const EventChannel channel = EventChannel('drag_and_drop_windows');

  TestWidgetsFlutterBinding.ensureInitialized();

  setUp(() {});

  tearDown(() {});

  test('getPlatformVersion', () async {
    // expect(await DragAndDropWindows.platformVersion, '42');
  });
}
