import '/backend/backend.dart';
import '/flutter_flow/flutter_flow_checkbox_group.dart';
import '/flutter_flow/flutter_flow_theme.dart';
import '/flutter_flow/flutter_flow_util.dart';
import '/flutter_flow/flutter_flow_widgets.dart';
import '/flutter_flow/form_field_controller.dart';
import '/custom_code/actions/index.dart' as actions;
import '/flutter_flow/custom_functions.dart' as functions;
import 'package:flutter/material.dart';
import 'notification_ending_model.dart';
export 'notification_ending_model.dart';

class NotificationEndingWidget extends StatefulWidget {
  const NotificationEndingWidget({
    super.key,
    required this.block,
    required this.type,
    this.tasks,
  });

  final BlocksRecord? block;
  final BlockTypesRecord? type;
  final List<String>? tasks;

  @override
  State<NotificationEndingWidget> createState() =>
      _NotificationEndingWidgetState();
}

class _NotificationEndingWidgetState extends State<NotificationEndingWidget> {
  late NotificationEndingModel _model;

  final scaffoldKey = GlobalKey<ScaffoldState>();

  @override
  void initState() {
    super.initState();
    _model = createModel(context, () => NotificationEndingModel());
  }

  @override
  void dispose() {
    _model.dispose();

    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return GestureDetector(
      onTap: () => _model.unfocusNode.canRequestFocus
          ? FocusScope.of(context).requestFocus(_model.unfocusNode)
          : FocusScope.of(context).unfocus(),
      child: Scaffold(
        key: scaffoldKey,
        backgroundColor: widget.type?.color,
        body: SafeArea(
          top: true,
          child: Align(
            alignment: const AlignmentDirectional(0.0, 0.0),
            child: Padding(
              padding: EdgeInsetsDirectional.fromSTEB(
                  valueOrDefault<double>(
                    5,
                    0.0,
                  ),
                  0.0,
                  valueOrDefault<double>(
                    5,
                    0.0,
                  ),
                  0.0),
              child: SingleChildScrollView(
                child: Column(
                  mainAxisSize: MainAxisSize.max,
                  mainAxisAlignment: MainAxisAlignment.center,
                  crossAxisAlignment: CrossAxisAlignment.center,
                  children: [
                    Padding(
                      padding:
                          const EdgeInsetsDirectional.fromSTEB(0.0, 0.0, 0.0, 30.0),
                      child: Icon(
                        Icons.query_builder,
                        color: FlutterFlowTheme.of(context).secondaryBackground,
                        size: 127.0,
                      ),
                    ),
                    Align(
                      alignment: const AlignmentDirectional(0.0, 0.0),
                      child: Padding(
                        padding: const EdgeInsetsDirectional.fromSTEB(
                            16.0, 0.0, 16.0, 8.0),
                        child: Text(
                          '${widget.type?.name} ending in 5 minutes',
                          textAlign: TextAlign.center,
                          style: FlutterFlowTheme.of(context)
                              .displayMedium
                              .override(
                                fontFamily: 'OpenDyslexic',
                                fontSize: 40.0,
                                letterSpacing: 0.0,
                                useGoogleFonts: false,
                              ),
                        ),
                      ),
                    ),
                    if (widget.tasks != null && (widget.tasks)!.isNotEmpty)
                      Column(
                        mainAxisSize: MainAxisSize.max,
                        children: [
                          Padding(
                            padding: const EdgeInsetsDirectional.fromSTEB(
                                16.0, 0.0, 16.0, 0.0),
                            child: Text(
                              'Mark finished tasks:',
                              textAlign: TextAlign.center,
                              style: FlutterFlowTheme.of(context)
                                  .displayMedium
                                  .override(
                                    fontFamily: 'OpenDyslexic',
                                    fontSize: 25.0,
                                    letterSpacing: 0.0,
                                    useGoogleFonts: false,
                                  ),
                            ),
                          ),
                          Padding(
                            padding: const EdgeInsetsDirectional.fromSTEB(
                                16.0, 0.0, 16.0, 0.0),
                            child: Container(
                              width: double.infinity,
                              height: 200.0,
                              decoration: const BoxDecoration(),
                              child: Padding(
                                padding: const EdgeInsetsDirectional.fromSTEB(
                                    0.0, 0.0, 0.0, 20.0),
                                child: FlutterFlowCheckboxGroup(
                                  options: widget.tasks!.toList(),
                                  onChanged: (val) => setState(
                                      () => _model.checkboxGroupValues = val),
                                  controller:
                                      _model.checkboxGroupValueController ??=
                                          FormFieldController<List<String>>(
                                    [],
                                  ),
                                  activeColor: functions
                                      .colorToSecondary(widget.type!.color!),
                                  checkColor: functions.colorGrayScaleValue(
                                              widget.type!.color!) >
                                          127
                                      ? FlutterFlowTheme.of(context).primaryText
                                      : FlutterFlowTheme.of(context).info,
                                  checkboxBorderColor: functions
                                      .colorToSecondary(widget.type!.color!),
                                  textStyle: FlutterFlowTheme.of(context)
                                      .bodyMedium
                                      .override(
                                        fontFamily: 'OpenDyslexic',
                                        color: const Color(0x8014181B),
                                        fontSize: 25.0,
                                        letterSpacing: 0.0,
                                        useGoogleFonts: false,
                                      ),
                                  unselectedTextStyle:
                                      FlutterFlowTheme.of(context)
                                          .bodyMedium
                                          .override(
                                            fontFamily: 'OpenDyslexic',
                                            fontSize: 25.0,
                                            letterSpacing: 0.0,
                                            fontWeight: FontWeight.normal,
                                            useGoogleFonts: false,
                                          ),
                                  checkboxBorderRadius:
                                      BorderRadius.circular(4.0),
                                  initialized:
                                      _model.checkboxGroupValues != null,
                                ),
                              ),
                            ),
                          ),
                        ],
                      ),
                    Align(
                      alignment: const AlignmentDirectional(0.0, 0.0),
                      child: FFButtonWidget(
                        onPressed: () async {
                          if (_model.checkboxGroupValues != null &&
                              (_model.checkboxGroupValues)!.isNotEmpty) {
                            await actions.deleteTasks(
                              widget.block!.reference,
                              _model.checkboxGroupValues!.toList(),
                            );
                          }
                          context.safePop();
                        },
                        text: 'OK',
                        options: FFButtonOptions(
                          height: 62.0,
                          padding: const EdgeInsetsDirectional.fromSTEB(
                              24.0, 0.0, 24.0, 0.0),
                          iconPadding: const EdgeInsetsDirectional.fromSTEB(
                              0.0, 0.0, 0.0, 0.0),
                          color: valueOrDefault<Color>(
                            functions.colorToSecondary(widget.type!.color!),
                            FlutterFlowTheme.of(context).secondary,
                          ),
                          textStyle:
                              FlutterFlowTheme.of(context).titleSmall.override(
                                    fontFamily: 'OpenDyslexic',
                                    color: widget.type?.color,
                                    fontSize: 25.0,
                                    letterSpacing: 0.0,
                                    useGoogleFonts: false,
                                  ),
                          elevation: 3.0,
                          borderSide: const BorderSide(
                            color: Colors.transparent,
                            width: 1.0,
                          ),
                          borderRadius: BorderRadius.circular(8.0),
                        ),
                      ),
                    ),
                  ],
                ),
              ),
            ),
          ),
        ),
      ),
    );
  }
}
