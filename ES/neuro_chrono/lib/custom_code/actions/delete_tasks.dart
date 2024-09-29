// Automatic FlutterFlow imports
import '/backend/backend.dart';
import '/backend/schema/enums/enums.dart';
import '/actions/actions.dart' as action_blocks;
import '/flutter_flow/flutter_flow_theme.dart';
import '/flutter_flow/flutter_flow_util.dart';
import 'index.dart'; // Imports other custom actions
import '/flutter_flow/custom_functions.dart'; // Imports custom functions
import 'package:flutter/material.dart';
// Begin custom action code
// DO NOT REMOVE OR MODIFY THE CODE ABOVE!

Future deleteTasks(
  DocumentReference document,
  List<String> tasks,
) async {
  var data = await document.get();
  List<dynamic>? updatedTasks = data.get("tasks");
  if (updatedTasks == null) return;
  updatedTasks.removeWhere((task) => tasks.contains(task));
  document.update({"tasks": updatedTasks});
}
