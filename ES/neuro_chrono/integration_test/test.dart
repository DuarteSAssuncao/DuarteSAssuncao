import 'package:flutter/gestures.dart';
import 'package:flutter/material.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:integration_test/integration_test.dart';
import 'package:neuro_chrono/flutter_flow/flutter_flow_drop_down.dart';
import 'package:neuro_chrono/flutter_flow/flutter_flow_icon_button.dart';
import 'package:neuro_chrono/flutter_flow/flutter_flow_widgets.dart';
import 'package:neuro_chrono/flutter_flow/flutter_flow_theme.dart';
import 'package:neuro_chrono/index.dart';
import 'package:neuro_chrono/main.dart';
import 'package:neuro_chrono/flutter_flow/flutter_flow_util.dart';

import 'package:provider/provider.dart';
import 'package:neuro_chrono/backend/firebase/firebase_config.dart';
import 'package:neuro_chrono/auth/firebase_auth/auth_util.dart';
import 'package:firebase_auth/firebase_auth.dart';

void main() async {
  IntegrationTestWidgetsFlutterBinding.ensureInitialized();

  setUpAll(() async {
    _overrideOnError();
    await initFirebase();
  });

  setUp(() async {
    await authManager.signOut();
    FFAppState.reset();
    final appState = FFAppState();
    await appState.initializePersistedState();
  });

  group('Test1', () {
    setUp(() async {
      await FirebaseAuth.instance.signInWithEmailAndPassword(
          email: 'test@neurochrone.pt', password: 'TestingPrototype');
    });

    testWidgets('See a block on the Planner Page', (WidgetTester tester) async {
      await tester.pumpWidget(ChangeNotifierProvider(
        create: (context) => FFAppState(),
        child: MyApp(
          entryPage: PlannerPageWidget(),
        ),
      ));

      await tester.tap(find.byKey(ValueKey('Friday_zzb5')));
      await tester.pumpAndSettle(
        Duration(milliseconds: 1000),
        EnginePhase.sendSemanticsUpdate,
        Duration(milliseconds: 3000),
      );
      expect(find.byKey(ValueKey('block_vsc7')), findsWidgets);
    });
  });
}

// There are certain types of errors that can happen during tests but
// should not break the test.
void _overrideOnError() {
  final originalOnError = FlutterError.onError!;
  FlutterError.onError = (errorDetails) {
    if (_shouldIgnoreError(errorDetails.toString())) {
      return;
    }
    originalOnError(errorDetails);
  };
}

bool _shouldIgnoreError(String error) {
  // It can fail to decode some SVGs - this should not break the test.
  if (error.contains('ImageCodecException')) {
    return true;
  }
  // Overflows happen all over the place,
  // but they should not break tests.
  if (error.contains('overflowed by')) {
    return true;
  }
  // Sometimes some images fail to load, it generally does not break the test.
  if (error.contains('No host specified in URI') ||
      error.contains('EXCEPTION CAUGHT BY IMAGE RESOURCE SERVICE')) {
    return true;
  }
  // These errors should be avoided, but they should not break the test.
  if (error.contains('setState() called after dispose()')) {
    return true;
  }

  return false;
}
