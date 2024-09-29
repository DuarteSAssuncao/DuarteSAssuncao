import 'package:flutter/material.dart';
import 'package:shared_preferences/shared_preferences.dart';

class FFAppState extends ChangeNotifier {
  static FFAppState _instance = FFAppState._internal();

  factory FFAppState() {
    return _instance;
  }

  FFAppState._internal();

  static void reset() {
    _instance = FFAppState._internal();
  }

  Future initializePersistedState() async {
    prefs = await SharedPreferences.getInstance();
    _safeInit(() {
      _volume = prefs.getDouble('ff_volume') ?? _volume;
    });
  }

  void update(VoidCallback callback) {
    callback();
    notifyListeners();
  }

  late SharedPreferences prefs;

  bool _fullScreenNotificationsOn = true;
  bool get fullScreenNotificationsOn => _fullScreenNotificationsOn;
  set fullScreenNotificationsOn(bool value) {
    _fullScreenNotificationsOn = value;
  }

  double _volume = 1.0;
  double get volume => _volume;
  set volume(double value) {
    _volume = value;
    prefs.setDouble('ff_volume', value);
  }

  double _speechRate = 0.75;
  double get speechRate => _speechRate;
  set speechRate(double value) {
    _speechRate = value;
  }
}

void _safeInit(Function() initializeField) {
  try {
    initializeField();
  } catch (_) {}
}

Future _safeInitAsync(Function() initializeField) async {
  try {
    await initializeField();
  } catch (_) {}
}
