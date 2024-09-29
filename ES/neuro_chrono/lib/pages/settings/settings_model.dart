import '/components/dropdown_widget.dart';
import '/flutter_flow/flutter_flow_util.dart';
import 'settings_widget.dart' show SettingsWidget;
import 'package:flutter/material.dart';

class SettingsModel extends FlutterFlowModel<SettingsWidget> {
  ///  State fields for stateful widgets in this page.

  final unfocusNode = FocusNode();
  // Model for dropdown component.
  late DropdownModel dropdownModel;
  // State field(s) for SwitchListTile widget.
  bool? switchListTileValue;
  // State field(s) for VolumeSlider widget.
  double? volumeSliderValue;
  // State field(s) for SpeechRateSlider widget.
  double? speechRateSliderValue;

  @override
  void initState(BuildContext context) {
    dropdownModel = createModel(context, () => DropdownModel());
  }

  @override
  void dispose() {
    unfocusNode.dispose();
    dropdownModel.dispose();
  }
}
