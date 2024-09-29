import '/flutter_flow/flutter_flow_util.dart';
import 'block_types_widget.dart' show BlockTypesWidget;
import 'package:flutter/material.dart';

class BlockTypesModel extends FlutterFlowModel<BlockTypesWidget> {
  ///  State fields for stateful widgets in this page.

  final unfocusNode = FocusNode();

  @override
  void initState(BuildContext context) {}

  @override
  void dispose() {
    unfocusNode.dispose();
  }
}
