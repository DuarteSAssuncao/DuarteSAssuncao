import '/flutter_flow/flutter_flow_util.dart';
import '/flutter_flow/form_field_controller.dart';
import 'edit_block_widget.dart' show EditBlockWidget;
import 'package:flutter/material.dart';

class EditBlockModel extends FlutterFlowModel<EditBlockWidget> {
  ///  State fields for stateful widgets in this page.

  final unfocusNode = FocusNode();
  final formKey = GlobalKey<FormState>();
  // State field(s) for blockType widget.
  String? blockTypeValue;
  FormFieldController<String>? blockTypeValueController;
  // State field(s) for weekDay widget.
  String? weekDayValue;
  FormFieldController<String>? weekDayValueController;
  DateTime? datePicked;
  // State field(s) for blockDuration widget.
  FocusNode? blockDurationFocusNode;
  TextEditingController? blockDurationTextController;
  String? Function(BuildContext, String?)? blockDurationTextControllerValidator;

  @override
  void initState(BuildContext context) {}

  @override
  void dispose() {
    unfocusNode.dispose();
    blockDurationFocusNode?.dispose();
    blockDurationTextController?.dispose();
  }
}
