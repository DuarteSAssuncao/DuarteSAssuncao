import '/flutter_flow/flutter_flow_util.dart';
import 'flashcards_widget.dart' show FlashcardsWidget;
import 'package:flutter/material.dart';

class FlashcardsModel extends FlutterFlowModel<FlashcardsWidget> {
  ///  State fields for stateful widgets in this page.

  final unfocusNode = FocusNode();

  @override
  void initState(BuildContext context) {}

  @override
  void dispose() {
    unfocusNode.dispose();
  }
}
