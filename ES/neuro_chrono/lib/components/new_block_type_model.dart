import '/flutter_flow/flutter_flow_util.dart';
import 'new_block_type_widget.dart' show NewBlockTypeWidget;
import 'package:flutter/material.dart';

class NewBlockTypeModel extends FlutterFlowModel<NewBlockTypeWidget> {
  ///  State fields for stateful widgets in this component.

  // State field(s) for TextField widget.
  FocusNode? textFieldFocusNode;
  TextEditingController? textController;
  String? Function(BuildContext, String?)? textControllerValidator;
  // Stores action output result for [Bottom Sheet - colorPicker] action in IconButton widget.
  Color? selectedColor;

  @override
  void initState(BuildContext context) {}

  @override
  void dispose() {
    textFieldFocusNode?.dispose();
    textController?.dispose();
  }
}
