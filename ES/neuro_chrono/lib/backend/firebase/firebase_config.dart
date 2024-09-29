import 'package:firebase_core/firebase_core.dart';
import 'package:flutter/foundation.dart';

Future initFirebase() async {
  if (kIsWeb) {
    await Firebase.initializeApp(
        options: const FirebaseOptions(
            apiKey: "AIzaSyCou3zvYjz-f_6KP2zKeRQTRFNxXSzswCg",
            authDomain: "neuro-chrono-hwbm3l.firebaseapp.com",
            projectId: "neuro-chrono-hwbm3l",
            storageBucket: "neuro-chrono-hwbm3l.appspot.com",
            messagingSenderId: "734669479955",
            appId: "1:734669479955:web:e05959962f987ef9a69fe6"));
  } else {
    await Firebase.initializeApp();
  }
}
