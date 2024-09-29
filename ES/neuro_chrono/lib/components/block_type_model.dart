import '/backend/backend.dart';
import '/flutter_flow/flutter_flow_util.dart';
import 'block_type_widget.dart' show BlockTypeWidget;
import 'package:expandable/expandable.dart';
import 'package:flutter/material.dart';

class BlockTypeModel extends FlutterFlowModel<BlockTypeWidget> {
  ///  Local state fields for this component.

  bool done = false;

  ///  State fields for stateful widgets in this component.

  final formKey = GlobalKey<FormState>();
  // State field(s) for Expandable widget.
  late ExpandableController expandableExpandableController;

  // State field(s) for TextField widget.
  FocusNode? textFieldFocusNode;
  TextEditingController? textController;
  String? Function(BuildContext, String?)? textControllerValidator;
  // Stores action output result for [Bottom Sheet - colorPicker] action in IconButton widget.
  Color? selectedColor;
  // Stores action output result for [Firestore Query - Query a collection] action in delete widget.
  List<BlocksRecord>? listOfBlocks;

  @override
  void initState(BuildContext context) {}

  @override
  void dispose() {
    expandableExpandableController.dispose();
    textFieldFocusNode?.dispose();
    textController?.dispose();
  }
}
