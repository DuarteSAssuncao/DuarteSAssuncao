import '/flutter_flow/flutter_flow_util.dart';
import 'block_view_widget.dart' show BlockViewWidget;
import 'package:flutter/material.dart';

class BlockViewModel extends FlutterFlowModel<BlockViewWidget> {
  ///  State fields for stateful widgets in this page.

  final unfocusNode = FocusNode();
  // Stores action output result for [Custom Action - taskMove] action in ListView widget.
  List<String>? updatedTasks;
  // State field(s) for NewTask widget.
  FocusNode? newTaskFocusNode;
  TextEditingController? newTaskTextController;
  String? Function(BuildContext, String?)? newTaskTextControllerValidator;

  @override
  void initState(BuildContext context) {}

  @override
  void dispose() {
    unfocusNode.dispose();
    newTaskFocusNode?.dispose();
    newTaskTextController?.dispose();
  }
}
