import '/backend/backend.dart';
import '/flutter_flow/flutter_flow_util.dart';
import '/flutter_flow/form_field_controller.dart';
import 'create_block_widget.dart' show CreateBlockWidget;
import 'package:flutter/material.dart';

class CreateBlockModel extends FlutterFlowModel<CreateBlockWidget> {
  ///  State fields for stateful widgets in this page.

  final unfocusNode = FocusNode();
  final formKey = GlobalKey<FormState>();
  // State field(s) for blockType widget.
  String? blockTypeValue;
  FormFieldController<String>? blockTypeValueController;
  DateTime? datePicked;
  // State field(s) for blockDuration widget.
  FocusNode? blockDurationFocusNode;
  TextEditingController? blockDurationTextController;
  String? Function(BuildContext, String?)? blockDurationTextControllerValidator;
  // State field(s) for Sunday widget.
  bool? sundayValue;
  // State field(s) for Monday widget.
  bool? mondayValue;
  // State field(s) for Tuesday widget.
  bool? tuesdayValue;
  // State field(s) for Wednesday widget.
  bool? wednesdayValue;
  // State field(s) for Thursday widget.
  bool? thursdayValue;
  // State field(s) for Friday widget.
  bool? fridayValue;
  // State field(s) for Saturday widget.
  bool? saturdayValue;
  // Stores action output result for [Firestore Query - Query a collection] action in Button widget.
  BlockTypesRecord? selectedBlockType;

  @override
  void initState(BuildContext context) {}

  @override
  void dispose() {
    unfocusNode.dispose();
    blockDurationFocusNode?.dispose();
    blockDurationTextController?.dispose();
  }
}
