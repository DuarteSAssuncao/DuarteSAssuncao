import '/auth/firebase_auth/auth_util.dart';
import '/backend/backend.dart';
import '/components/color_picker_widget.dart';
import '/flutter_flow/flutter_flow_icon_button.dart';
import '/flutter_flow/flutter_flow_theme.dart';
import '/flutter_flow/flutter_flow_util.dart';
import '/custom_code/actions/index.dart' as actions;
import 'package:expandable/expandable.dart';
import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:font_awesome_flutter/font_awesome_flutter.dart';
import 'block_type_model.dart';
export 'block_type_model.dart';

class BlockTypeWidget extends StatefulWidget {
  const BlockTypeWidget({
    super.key,
    this.blockTypeDoc,
    required this.name,
    required this.color,
  });

  final DocumentReference? blockTypeDoc;
  final String? name;
  final Color? color;

  @override
  State<BlockTypeWidget> createState() => _BlockTypeWidgetState();
}

class _BlockTypeWidgetState extends State<BlockTypeWidget> {
  late BlockTypeModel _model;

  @override
  void setState(VoidCallback callback) {
    super.setState(callback);
    _model.onUpdate();
  }

  @override
  void initState() {
    super.initState();
    _model = createModel(context, () => BlockTypeModel());

    _model.expandableExpandableController =
        ExpandableController(initialExpanded: false);
    _model.textController ??= TextEditingController(text: widget.name);
    _model.textFieldFocusNode ??= FocusNode();
  }

  @override
  void dispose() {
    _model.maybeDispose();

    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return Padding(
      padding: const EdgeInsetsDirectional.fromSTEB(6.0, 0.0, 6.0, 0.0),
      child: Card(
        clipBehavior: Clip.antiAliasWithSaveLayer,
        color: widget.color,
        elevation: 4.0,
        shape: RoundedRectangleBorder(
          borderRadius: BorderRadius.circular(8.0),
        ),
        child: Container(
          width: double.infinity,
          color: const Color(0x00000000),
          child: ExpandableNotifier(
            controller: _model.expandableExpandableController,
            child: ExpandablePanel(
              header: Padding(
                padding: const EdgeInsetsDirectional.fromSTEB(16.0, 8.0, 8.0, 8.0),
                child: Text(
                  valueOrDefault<String>(
                    widget.name,
                    'Custom',
                  ),
                  style: FlutterFlowTheme.of(context).headlineSmall.override(
                        fontFamily: 'OpenDyslexic',
                        letterSpacing: 0.0,
                        useGoogleFonts: false,
                      ),
                ),
              ),
              collapsed: Align(
                alignment: const AlignmentDirectional(0.0, 0.0),
                child: Container(
                  width: 0.0,
                  height: 8.0,
                  decoration: BoxDecoration(
                    color: FlutterFlowTheme.of(context).secondaryBackground,
                  ),
                ),
              ),
              expanded: Form(
                key: _model.formKey,
                autovalidateMode: AutovalidateMode.disabled,
                child: Padding(
                  padding: const EdgeInsetsDirectional.fromSTEB(8.0, 0.0, 8.0, 0.0),
                  child: Column(
                    mainAxisSize: MainAxisSize.max,
                    children: [
                      Padding(
                        padding:
                            const EdgeInsetsDirectional.fromSTEB(0.0, 8.0, 0.0, 8.0),
                        child: Row(
                          mainAxisSize: MainAxisSize.max,
                          children: [
                            Expanded(
                              child: Align(
                                alignment: const AlignmentDirectional(0.0, 0.0),
                                child: TextFormField(
                                  controller: _model.textController,
                                  focusNode: _model.textFieldFocusNode,
                                  autofocus: false,
                                  textCapitalization: TextCapitalization.words,
                                  obscureText: false,
                                  decoration: InputDecoration(
                                    labelText: 'New Block Type Name',
                                    labelStyle: FlutterFlowTheme.of(context)
                                        .bodyLarge
                                        .override(
                                          fontFamily: 'OpenDyslexic',
                                          letterSpacing: 0.0,
                                          useGoogleFonts: false,
                                        ),
                                    alignLabelWithHint: false,
                                    enabledBorder: OutlineInputBorder(
                                      borderSide: BorderSide(
                                        color: FlutterFlowTheme.of(context)
                                            .primary,
                                        width: 2.0,
                                      ),
                                      borderRadius: BorderRadius.circular(8.0),
                                    ),
                                    focusedBorder: OutlineInputBorder(
                                      borderSide: BorderSide(
                                        color: FlutterFlowTheme.of(context)
                                            .primary,
                                        width: 2.0,
                                      ),
                                      borderRadius: BorderRadius.circular(8.0),
                                    ),
                                    errorBorder: OutlineInputBorder(
                                      borderSide: BorderSide(
                                        color:
                                            FlutterFlowTheme.of(context).error,
                                        width: 2.0,
                                      ),
                                      borderRadius: BorderRadius.circular(8.0),
                                    ),
                                    focusedErrorBorder: OutlineInputBorder(
                                      borderSide: BorderSide(
                                        color:
                                            FlutterFlowTheme.of(context).error,
                                        width: 2.0,
                                      ),
                                      borderRadius: BorderRadius.circular(8.0),
                                    ),
                                  ),
                                  style: FlutterFlowTheme.of(context)
                                      .bodyLarge
                                      .override(
                                        fontFamily: 'OpenDyslexic',
                                        letterSpacing: 0.0,
                                        useGoogleFonts: false,
                                      ),
                                  maxLength: 20,
                                  maxLengthEnforcement:
                                      MaxLengthEnforcement.enforced,
                                  buildCounter: (context,
                                          {required currentLength,
                                          required isFocused,
                                          maxLength}) =>
                                      null,
                                  validator: _model.textControllerValidator
                                      .asValidator(context),
                                ),
                              ),
                            ),
                            Align(
                              alignment: const AlignmentDirectional(0.0, 0.0),
                              child: Padding(
                                padding: const EdgeInsetsDirectional.fromSTEB(
                                    8.0, 0.0, 0.0, 0.0),
                                child: FlutterFlowIconButton(
                                  borderColor: valueOrDefault<Color>(
                                    _model.selectedColor,
                                    FlutterFlowTheme.of(context).primary,
                                  ),
                                  borderRadius: 23.0,
                                  borderWidth: 7.0,
                                  buttonSize: 48.0,
                                  fillColor:
                                      FlutterFlowTheme.of(context).primary,
                                  icon: Icon(
                                    Icons.color_lens,
                                    color: FlutterFlowTheme.of(context).info,
                                    size: 30.0,
                                  ),
                                  onPressed: () async {
                                    await showModalBottomSheet(
                                      isScrollControlled: true,
                                      backgroundColor: Colors.transparent,
                                      enableDrag: false,
                                      context: context,
                                      builder: (context) {
                                        return Padding(
                                          padding:
                                              MediaQuery.viewInsetsOf(context),
                                          child: const ColorPickerWidget(),
                                        );
                                      },
                                    ).then((value) => safeSetState(
                                        () => _model.selectedColor = value));

                                    setState(() {});
                                  },
                                ),
                              ),
                            ),
                          ],
                        ),
                      ),
                      Padding(
                        padding:
                            const EdgeInsetsDirectional.fromSTEB(8.0, 8.0, 8.0, 8.0),
                        child: Row(
                          mainAxisSize: MainAxisSize.max,
                          mainAxisAlignment: MainAxisAlignment.spaceEvenly,
                          children: [
                            FlutterFlowIconButton(
                              borderRadius: 8.0,
                              borderWidth: 0.0,
                              buttonSize: 40.0,
                              fillColor: widget.color,
                              icon: const FaIcon(
                                FontAwesomeIcons.trashAlt,
                                color: Color(0xFFFF2222),
                                size: 24.0,
                              ),
                              onPressed: () async {
                                var confirmDialogResponse =
                                    await showDialog<bool>(
                                          context: context,
                                          builder: (alertDialogContext) {
                                            return AlertDialog(
                                              title: const Text('Delete Type'),
                                              content: const Text(
                                                  'Are you sure you want to delete this Block Type? If you do this, you will be deleting all the blocks with this type.'),
                                              actions: [
                                                TextButton(
                                                  onPressed: () =>
                                                      Navigator.pop(
                                                          alertDialogContext,
                                                          false),
                                                  child: const Text('Cancel'),
                                                ),
                                                TextButton(
                                                  onPressed: () =>
                                                      Navigator.pop(
                                                          alertDialogContext,
                                                          true),
                                                  child: const Text('Delete'),
                                                ),
                                              ],
                                            );
                                          },
                                        ) ??
                                        false;
                                if (confirmDialogResponse) {
                                  _model.listOfBlocks =
                                      await queryBlocksRecordOnce(
                                    queryBuilder: (blocksRecord) => blocksRecord
                                        .where(
                                          'userId',
                                          isEqualTo: currentUserUid,
                                        )
                                        .where(
                                          'type',
                                          isEqualTo: widget.blockTypeDoc,
                                        ),
                                    limit: 1000,
                                  );
                                  await actions.deleteListOfBlocks(
                                    _model.listOfBlocks!
                                        .map((e) => e.reference)
                                        .toList(),
                                  );
                                  await widget.blockTypeDoc!.delete();
                                } else {
                                  Navigator.pop(context);
                                }

                                context.goNamed('BlockTypes');

                                setState(() {});
                              },
                            ),
                            SizedBox(
                              height: 40.0,
                              child: VerticalDivider(
                                thickness: 1.0,
                                color:
                                    FlutterFlowTheme.of(context).secondaryText,
                              ),
                            ),
                            FlutterFlowIconButton(
                              borderRadius: 8.0,
                              borderWidth: 0.0,
                              buttonSize: 40.0,
                              fillColor: widget.color,
                              icon: FaIcon(
                                FontAwesomeIcons.check,
                                color: FlutterFlowTheme.of(context).success,
                                size: 24.0,
                              ),
                              onPressed: () async {
                                await widget.blockTypeDoc!
                                    .update(createBlockTypesRecordData(
                                  name: _model.textController.text == ''
                                      ? widget.name
                                      : _model.textController.text,
                                  color: _model.selectedColor ?? widget.color,
                                ));
                                ScaffoldMessenger.of(context).showSnackBar(
                                  SnackBar(
                                    content: Text(
                                      'Block Type successfully updated!',
                                      style: FlutterFlowTheme.of(context)
                                          .bodyMedium
                                          .override(
                                            fontFamily: 'OpenDyslexic',
                                            color: FlutterFlowTheme.of(context)
                                                .info,
                                            letterSpacing: 0.0,
                                            useGoogleFonts: false,
                                          ),
                                    ),
                                    duration: const Duration(milliseconds: 3000),
                                    backgroundColor:
                                        FlutterFlowTheme.of(context).success,
                                  ),
                                );
                              },
                            ),
                          ],
                        ),
                      ),
                    ],
                  ),
                ),
              ),
              theme: ExpandableThemeData(
                tapHeaderToExpand: true,
                tapBodyToExpand: false,
                tapBodyToCollapse: false,
                headerAlignment: ExpandablePanelHeaderAlignment.center,
                hasIcon: true,
                expandIcon: FontAwesomeIcons.pen,
                collapseIcon: FontAwesomeIcons.times,
                iconSize: 24.0,
                iconColor: FlutterFlowTheme.of(context).primary,
                iconPadding: const EdgeInsets.fromLTRB(0.0, 16.0, 16.0, 8.0),
              ),
            ),
          ),
        ),
      ),
    );
  }
}
