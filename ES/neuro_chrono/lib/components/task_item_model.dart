import '/flutter_flow/flutter_flow_util.dart';
import 'task_item_widget.dart' show TaskItemWidget;
import 'package:expandable/expandable.dart';
import 'package:flutter/material.dart';

class TaskItemModel extends FlutterFlowModel<TaskItemWidget> {
  ///  State fields for stateful widgets in this component.

  final formKey = GlobalKey<FormState>();
  // State field(s) for Expandable widget.
  late ExpandableController expandableExpandableController;

  // State field(s) for TextField widget.
  FocusNode? textFieldFocusNode;
  TextEditingController? textController;
  String? Function(BuildContext, String?)? textControllerValidator;
  // Stores action output result for [Custom Action - taskModify] action in save widget.
  List<String>? updatedTasks;

  @override
  void initState(BuildContext context) {}

  @override
  void dispose() {
    expandableExpandableController.dispose();
    textFieldFocusNode?.dispose();
    textController?.dispose();
  }
}
