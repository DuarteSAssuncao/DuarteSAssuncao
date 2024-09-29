import '/components/block_widget.dart';
import '/flutter_flow/flutter_flow_util.dart';
import 'planner_page_widget.dart' show PlannerPageWidget;
import 'package:flutter/material.dart';

class PlannerPageModel extends FlutterFlowModel<PlannerPageWidget> {
  ///  State fields for stateful widgets in this page.

  final unfocusNode = FocusNode();
  // State field(s) for TabBar widget.
  TabController? tabBarController;
  int get tabBarCurrentIndex =>
      tabBarController != null ? tabBarController!.index : 0;

  // Models for block dynamic component.
  late FlutterFlowDynamicModels<BlockModel> blockModels1;
  // Models for block dynamic component.
  late FlutterFlowDynamicModels<BlockModel> blockModels2;
  // Models for block dynamic component.
  late FlutterFlowDynamicModels<BlockModel> blockModels3;
  // Models for block dynamic component.
  late FlutterFlowDynamicModels<BlockModel> blockModels4;
  // Models for block dynamic component.
  late FlutterFlowDynamicModels<BlockModel> blockModels5;
  // Models for block dynamic component.
  late FlutterFlowDynamicModels<BlockModel> blockModels6;
  // Models for block dynamic component.
  late FlutterFlowDynamicModels<BlockModel> blockModels7;

  @override
  void initState(BuildContext context) {
    blockModels1 = FlutterFlowDynamicModels(() => BlockModel());
    blockModels2 = FlutterFlowDynamicModels(() => BlockModel());
    blockModels3 = FlutterFlowDynamicModels(() => BlockModel());
    blockModels4 = FlutterFlowDynamicModels(() => BlockModel());
    blockModels5 = FlutterFlowDynamicModels(() => BlockModel());
    blockModels6 = FlutterFlowDynamicModels(() => BlockModel());
    blockModels7 = FlutterFlowDynamicModels(() => BlockModel());
  }

  @override
  void dispose() {
    unfocusNode.dispose();
    tabBarController?.dispose();
    blockModels1.dispose();
    blockModels2.dispose();
    blockModels3.dispose();
    blockModels4.dispose();
    blockModels5.dispose();
    blockModels6.dispose();
    blockModels7.dispose();
  }
}
