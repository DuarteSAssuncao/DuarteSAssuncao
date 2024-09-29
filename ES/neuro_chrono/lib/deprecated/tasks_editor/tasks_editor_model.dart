import '/flutter_flow/flutter_flow_util.dart';
import 'tasks_editor_widget.dart' show TasksEditorWidget;
import 'package:flutter/material.dart';

class TasksEditorModel extends FlutterFlowModel<TasksEditorWidget> {
  ///  State fields for stateful widgets in this component.

  // State field(s) for newTaskName widget.
  FocusNode? newTaskNameFocusNode;
  TextEditingController? newTaskNameTextController;
  String? Function(BuildContext, String?)? newTaskNameTextControllerValidator;
  // Stores action output result for [Custom Action - taskMove] action in ListView widget.
  List<String>? updatedTasks;

  @override
  void initState(BuildContext context) {}

  @override
  void dispose() {
    newTaskNameFocusNode?.dispose();
    newTaskNameTextController?.dispose();
  }
}
