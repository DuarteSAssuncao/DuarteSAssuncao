import '/flutter_flow/flutter_flow_util.dart';
import 'edit_flashcard_widget.dart' show EditFlashcardWidget;
import 'package:flutter/material.dart';

class EditFlashcardModel extends FlutterFlowModel<EditFlashcardWidget> {
  ///  State fields for stateful widgets in this page.

  final unfocusNode = FocusNode();
  final formKey = GlobalKey<FormState>();
  // State field(s) for Title widget.
  FocusNode? titleFocusNode;
  TextEditingController? titleTextController;
  String? Function(BuildContext, String?)? titleTextControllerValidator;
  // State field(s) for Subtitle widget.
  FocusNode? subtitleFocusNode;
  TextEditingController? subtitleTextController;
  String? Function(BuildContext, String?)? subtitleTextControllerValidator;
  // State field(s) for Content widget.
  FocusNode? contentFocusNode;
  TextEditingController? contentTextController;
  String? Function(BuildContext, String?)? contentTextControllerValidator;

  @override
  void initState(BuildContext context) {}

  @override
  void dispose() {
    unfocusNode.dispose();
    titleFocusNode?.dispose();
    titleTextController?.dispose();

    subtitleFocusNode?.dispose();
    subtitleTextController?.dispose();

    contentFocusNode?.dispose();
    contentTextController?.dispose();
  }
}
