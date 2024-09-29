import '/auth/firebase_auth/auth_util.dart';
import '/backend/backend.dart';
import '/backend/schema/enums/enums.dart';
import '/flutter_flow/flutter_flow_drop_down.dart';
import '/flutter_flow/flutter_flow_icon_button.dart';
import '/flutter_flow/flutter_flow_theme.dart';
import '/flutter_flow/flutter_flow_util.dart';
import '/flutter_flow/flutter_flow_widgets.dart';
import '/flutter_flow/form_field_controller.dart';
import 'dart:async';
import '/flutter_flow/custom_functions.dart' as functions;
import 'package:flutter/material.dart';
import 'edit_block_model.dart';
export 'edit_block_model.dart';

class EditBlockWidget extends StatefulWidget {
  const EditBlockWidget({
    super.key,
    required this.type,
    required this.day,
    required this.startingTime,
    required this.duration,
    required this.block,
    required this.tasks,
  });

  final BlockTypesRecord? type;
  final WeekDay? day;
  final int? startingTime;
  final int? duration;
  final BlocksRecord? block;
  final List<String>? tasks;

  @override
  State<EditBlockWidget> createState() => _EditBlockWidgetState();
}

class _EditBlockWidgetState extends State<EditBlockWidget> {
  late EditBlockModel _model;

  final scaffoldKey = GlobalKey<ScaffoldState>();

  @override
  void initState() {
    super.initState();
    _model = createModel(context, () => EditBlockModel());

    _model.blockDurationTextController ??=
        TextEditingController(text: widget.duration?.toString());
    _model.blockDurationFocusNode ??= FocusNode();
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
        backgroundColor: FlutterFlowTheme.of(context).secondaryBackground,
        appBar: AppBar(
          backgroundColor: FlutterFlowTheme.of(context).secondaryBackground,
          automaticallyImplyLeading: false,
          title: Column(
            mainAxisSize: MainAxisSize.max,
            crossAxisAlignment: CrossAxisAlignment.start,
            children: [
              Text(
                'Block Settings',
                style: FlutterFlowTheme.of(context).headlineMedium.override(
                      fontFamily: 'OpenDyslexic',
                      letterSpacing: 0.0,
                      useGoogleFonts: false,
                    ),
              ),
            ].divide(const SizedBox(height: 4.0)),
          ),
          actions: [
            Padding(
              padding: const EdgeInsetsDirectional.fromSTEB(0.0, 8.0, 12.0, 8.0),
              child: FlutterFlowIconButton(
                borderColor: FlutterFlowTheme.of(context).primary,
                borderRadius: 12.0,
                borderWidth: 2.0,
                buttonSize: 40.0,
                fillColor: FlutterFlowTheme.of(context).secondaryBackground,
                icon: Icon(
                  Icons.close_rounded,
                  color: FlutterFlowTheme.of(context).primaryText,
                  size: 24.0,
                ),
                onPressed: () async {
                  context.safePop();
                },
              ),
            ),
          ],
          centerTitle: false,
          elevation: 0.0,
        ),
        body: SafeArea(
          top: true,
          child: StreamBuilder<List<BlockTypesRecord>>(
            stream: queryBlockTypesRecord(
              queryBuilder: (blockTypesRecord) => blockTypesRecord
                  .where(
                    'userId',
                    isEqualTo: currentUserUid,
                  )
                  .orderBy('name'),
            ),
            builder: (context, snapshot) {
              // Customize what your widget looks like when it's loading.
              if (!snapshot.hasData) {
                return Center(
                  child: SizedBox(
                    width: 50.0,
                    height: 50.0,
                    child: CircularProgressIndicator(
                      valueColor: AlwaysStoppedAnimation<Color>(
                        FlutterFlowTheme.of(context).primary,
                      ),
                    ),
                  ),
                );
              }
              List<BlockTypesRecord> formBlockTypesRecordList = snapshot.data!;
              return Form(
                key: _model.formKey,
                autovalidateMode: AutovalidateMode.disabled,
                child: Padding(
                  padding:
                      const EdgeInsetsDirectional.fromSTEB(16.0, 12.0, 16.0, 0.0),
                  child: Column(
                    mainAxisSize: MainAxisSize.max,
                    crossAxisAlignment: CrossAxisAlignment.start,
                    children: [
                      FlutterFlowDropDown<String>(
                        controller: _model.blockTypeValueController ??=
                            FormFieldController<String>(
                          _model.blockTypeValue ??= widget.type?.name,
                        ),
                        options: formBlockTypesRecordList
                            .map((e) => e.name)
                            .toList(),
                        onChanged: (val) =>
                            setState(() => _model.blockTypeValue = val),
                        width: double.infinity,
                        height: 62.0,
                        textStyle:
                            FlutterFlowTheme.of(context).bodyLarge.override(
                                  fontFamily: 'OpenDyslexic',
                                  letterSpacing: 0.0,
                                  useGoogleFonts: false,
                                ),
                        icon: Icon(
                          Icons.keyboard_arrow_down_rounded,
                          color: FlutterFlowTheme.of(context).secondaryText,
                          size: 24.0,
                        ),
                        fillColor:
                            FlutterFlowTheme.of(context).secondaryBackground,
                        elevation: 2.0,
                        borderColor: FlutterFlowTheme.of(context).primary,
                        borderWidth: 2.0,
                        borderRadius: 12.0,
                        margin:
                            const EdgeInsetsDirectional.fromSTEB(12.0, 4.0, 8.0, 4.0),
                        hidesUnderline: true,
                        isOverButton: true,
                        isSearchable: false,
                        isMultiSelect: false,
                        labelText: 'Block Type',
                        labelTextStyle:
                            FlutterFlowTheme.of(context).labelLarge.override(
                                  fontFamily: 'OpenDyslexic',
                                  letterSpacing: 0.0,
                                  useGoogleFonts: false,
                                ),
                      ),
                      FlutterFlowDropDown<String>(
                        controller: _model.weekDayValueController ??=
                            FormFieldController<String>(
                          _model.weekDayValue ??= widget.day?.name,
                        ),
                        options: const [
                          'Monday',
                          'Tuesday',
                          'Wednesday',
                          'Thursday',
                          'Friday',
                          'Saturday',
                          'Sunday'
                        ],
                        onChanged: (val) =>
                            setState(() => _model.weekDayValue = val),
                        width: double.infinity,
                        height: 62.0,
                        textStyle:
                            FlutterFlowTheme.of(context).bodyLarge.override(
                                  fontFamily: 'OpenDyslexic',
                                  letterSpacing: 0.0,
                                  useGoogleFonts: false,
                                ),
                        icon: Icon(
                          Icons.keyboard_arrow_down_rounded,
                          color: FlutterFlowTheme.of(context).secondaryText,
                          size: 24.0,
                        ),
                        fillColor:
                            FlutterFlowTheme.of(context).secondaryBackground,
                        elevation: 2.0,
                        borderColor: FlutterFlowTheme.of(context).primary,
                        borderWidth: 2.0,
                        borderRadius: 12.0,
                        margin:
                            const EdgeInsetsDirectional.fromSTEB(12.0, 4.0, 8.0, 4.0),
                        hidesUnderline: true,
                        isOverButton: true,
                        isSearchable: false,
                        isMultiSelect: false,
                        labelText: 'Week Day',
                        labelTextStyle:
                            FlutterFlowTheme.of(context).labelLarge.override(
                                  fontFamily: 'OpenDyslexic',
                                  letterSpacing: 0.0,
                                  useGoogleFonts: false,
                                ),
                      ),
                      FFButtonWidget(
                        onPressed: () async {
                          final datePickedTime = await showTimePicker(
                            context: context,
                            initialTime: TimeOfDay.fromDateTime((functions
                                    .intToDatetime(widget.startingTime!) ??
                                DateTime.now())),
                            builder: (context, child) {
                              return wrapInMaterialTimePickerTheme(
                                context,
                                child!,
                                headerBackgroundColor:
                                    FlutterFlowTheme.of(context).primary,
                                headerForegroundColor:
                                    FlutterFlowTheme.of(context).info,
                                headerTextStyle: FlutterFlowTheme.of(context)
                                    .headlineLarge
                                    .override(
                                      fontFamily: 'OpenDyslexic',
                                      fontSize: 32.0,
                                      letterSpacing: 0.0,
                                      fontWeight: FontWeight.w600,
                                      useGoogleFonts: false,
                                    ),
                                pickerBackgroundColor:
                                    FlutterFlowTheme.of(context)
                                        .secondaryBackground,
                                pickerForegroundColor:
                                    FlutterFlowTheme.of(context).primaryText,
                                selectedDateTimeBackgroundColor:
                                    FlutterFlowTheme.of(context).primary,
                                selectedDateTimeForegroundColor:
                                    FlutterFlowTheme.of(context).info,
                                actionButtonForegroundColor:
                                    FlutterFlowTheme.of(context).primaryText,
                                iconSize: 24.0,
                              );
                            },
                          );
                          if (datePickedTime != null) {
                            safeSetState(() {
                              _model.datePicked = DateTime(
                                (functions.intToDatetime(
                                            widget.startingTime!) ??
                                        DateTime.now())
                                    .year,
                                (functions.intToDatetime(
                                            widget.startingTime!) ??
                                        DateTime.now())
                                    .month,
                                (functions.intToDatetime(
                                            widget.startingTime!) ??
                                        DateTime.now())
                                    .day,
                                datePickedTime.hour,
                                datePickedTime.minute,
                              );
                            });
                          }
                        },
                        text:
                            'Starting Time: ${functions.timeToString(functions.dateTimeToInt(_model.datePicked != null ? _model.datePicked! : functions.intToDatetime(widget.startingTime!)!))}',
                        options: FFButtonOptions(
                          width: double.infinity,
                          height: 62.0,
                          padding: const EdgeInsetsDirectional.fromSTEB(
                              0.0, 0.0, 0.0, 0.0),
                          iconPadding: const EdgeInsetsDirectional.fromSTEB(
                              0.0, 0.0, 0.0, 0.0),
                          color:
                              FlutterFlowTheme.of(context).secondaryBackground,
                          textStyle:
                              FlutterFlowTheme.of(context).bodyLarge.override(
                                    fontFamily: 'OpenDyslexic',
                                    letterSpacing: 0.0,
                                    useGoogleFonts: false,
                                  ),
                          elevation: 0.0,
                          borderSide: BorderSide(
                            color: FlutterFlowTheme.of(context).primary,
                            width: 2.0,
                          ),
                          borderRadius: BorderRadius.circular(12.0),
                        ),
                      ),
                      TextFormField(
                        controller: _model.blockDurationTextController,
                        focusNode: _model.blockDurationFocusNode,
                        autofocus: false,
                        obscureText: false,
                        decoration: InputDecoration(
                          isDense: false,
                          labelText: 'Duration (min)',
                          labelStyle: FlutterFlowTheme.of(context)
                              .labelLarge
                              .override(
                                fontFamily: 'OpenDyslexic',
                                color: FlutterFlowTheme.of(context).primaryText,
                                letterSpacing: 0.0,
                                useGoogleFonts: false,
                              ),
                          hintStyle:
                              FlutterFlowTheme.of(context).labelMedium.override(
                                    fontFamily: 'OpenDyslexic',
                                    letterSpacing: 0.0,
                                    useGoogleFonts: false,
                                  ),
                          enabledBorder: OutlineInputBorder(
                            borderSide: BorderSide(
                              color: FlutterFlowTheme.of(context).primary,
                              width: 2.0,
                            ),
                            borderRadius: BorderRadius.circular(12.0),
                          ),
                          focusedBorder: OutlineInputBorder(
                            borderSide: BorderSide(
                              color: FlutterFlowTheme.of(context).primary,
                              width: 2.0,
                            ),
                            borderRadius: BorderRadius.circular(12.0),
                          ),
                          errorBorder: OutlineInputBorder(
                            borderSide: BorderSide(
                              color: FlutterFlowTheme.of(context).error,
                              width: 2.0,
                            ),
                            borderRadius: BorderRadius.circular(12.0),
                          ),
                          focusedErrorBorder: OutlineInputBorder(
                            borderSide: BorderSide(
                              color: FlutterFlowTheme.of(context).error,
                              width: 2.0,
                            ),
                            borderRadius: BorderRadius.circular(12.0),
                          ),
                        ),
                        style: FlutterFlowTheme.of(context).bodyLarge.override(
                              fontFamily: 'OpenDyslexic',
                              letterSpacing: 0.0,
                              useGoogleFonts: false,
                            ),
                        validator: _model.blockDurationTextControllerValidator
                            .asValidator(context),
                      ),
                      Expanded(
                        child: Container(
                          width: 100.0,
                          height: 200.0,
                          constraints: const BoxConstraints(
                            minWidth: double.infinity,
                            maxWidth: double.infinity,
                            maxHeight: double.infinity,
                          ),
                          decoration: BoxDecoration(
                            color: FlutterFlowTheme.of(context)
                                .secondaryBackground,
                          ),
                        ),
                      ),
                      Align(
                        alignment: const AlignmentDirectional(0.0, 1.0),
                        child: StreamBuilder<List<BlocksRecord>>(
                          stream: queryBlocksRecord(
                            queryBuilder: (blocksRecord) => blocksRecord
                                .where(
                                  'userId',
                                  isEqualTo: currentUserUid,
                                )
                                .orderBy('start'),
                          ),
                          builder: (context, snapshot) {
                            // Customize what your widget looks like when it's loading.
                            if (!snapshot.hasData) {
                              return Center(
                                child: SizedBox(
                                  width: 50.0,
                                  height: 50.0,
                                  child: CircularProgressIndicator(
                                    valueColor: AlwaysStoppedAnimation<Color>(
                                      FlutterFlowTheme.of(context).primary,
                                    ),
                                  ),
                                ),
                              );
                            }
                            List<BlocksRecord> buttonBlocksRecordList =
                                snapshot.data!;
                            return FFButtonWidget(
                              onPressed: () async {
                                if (functions.doesIntercept(
                                    buttonBlocksRecordList
                                        .where((e) =>
                                            widget.block?.reference !=
                                            e.reference)
                                        .toList(),
                                    _model.datePicked == null
                                        ? widget.startingTime!
                                        : functions
                                            .dateTimeToInt(_model.datePicked!),
                                    _model.blockDurationTextController
                                                    .text ==
                                                ''
                                        ? widget.duration!
                                        : int.parse(_model
                                            .blockDurationTextController.text),
                                    _model.weekDayValue == null ||
                                            _model.weekDayValue == ''
                                        ? widget.day
                                        : functions.stringToWeekDay(
                                            _model.weekDayValue!))) {
                                  ScaffoldMessenger.of(context).showSnackBar(
                                    SnackBar(
                                      content: Text(
                                        'The current block intercepts another block!',
                                        style: FlutterFlowTheme.of(context)
                                            .labelMedium
                                            .override(
                                              fontFamily: 'OpenDyslexic',
                                              color:
                                                  FlutterFlowTheme.of(context)
                                                      .secondaryBackground,
                                              letterSpacing: 0.0,
                                              useGoogleFonts: false,
                                            ),
                                      ),
                                      duration: const Duration(milliseconds: 4000),
                                      backgroundColor:
                                          FlutterFlowTheme.of(context).error,
                                    ),
                                  );
                                } else {
                                  unawaited(
                                    () async {
                                      await widget.block!.reference
                                          .update(createBlocksRecordData(
                                        type: formBlockTypesRecordList
                                            .where((e) =>
                                                e.name == _model.blockTypeValue)
                                            .toList()
                                            .first
                                            .reference,
                                        weekDay: _model.weekDayValue == null ||
                                                _model.weekDayValue == ''
                                            ? widget.day
                                            : functions.stringToWeekDay(
                                                _model.weekDayValue!),
                                        duration: _model.blockDurationTextController
                                                        .text ==
                                                    ''
                                            ? widget.duration
                                            : int.tryParse(_model
                                                .blockDurationTextController
                                                .text),
                                        userId: currentUserUid,
                                        start: _model.datePicked == null
                                            ? widget.startingTime
                                            : functions.dateTimeToInt(
                                                _model.datePicked!),
                                      ));
                                    }(),
                                  );
                                  context.safePop();
                                }
                              },
                              text: 'Save Changes',
                              options: FFButtonOptions(
                                width: double.infinity,
                                height: 62.0,
                                padding: const EdgeInsetsDirectional.fromSTEB(
                                    24.0, 0.0, 24.0, 0.0),
                                iconPadding: const EdgeInsetsDirectional.fromSTEB(
                                    0.0, 0.0, 0.0, 0.0),
                                color: FlutterFlowTheme.of(context).primary,
                                textStyle: FlutterFlowTheme.of(context)
                                    .titleMedium
                                    .override(
                                      fontFamily: 'OpenDyslexic',
                                      letterSpacing: 0.0,
                                      useGoogleFonts: false,
                                    ),
                                elevation: 4.0,
                                borderSide: const BorderSide(
                                  color: Colors.transparent,
                                  width: 1.0,
                                ),
                                borderRadius: BorderRadius.circular(12.0),
                              ),
                            );
                          },
                        ),
                      ),
                      Align(
                        alignment: const AlignmentDirectional(0.0, 1.0),
                        child: FFButtonWidget(
                          onPressed: () async {
                            unawaited(
                              () async {
                                await widget.block!.reference.delete();
                              }(),
                            );
                            context.safePop();
                            context.safePop();
                          },
                          text: 'Delete',
                          options: FFButtonOptions(
                            width: double.infinity,
                            height: 62.0,
                            padding: const EdgeInsetsDirectional.fromSTEB(
                                24.0, 0.0, 24.0, 0.0),
                            iconPadding: const EdgeInsetsDirectional.fromSTEB(
                                0.0, 0.0, 0.0, 20.0),
                            color: FlutterFlowTheme.of(context).error,
                            textStyle: FlutterFlowTheme.of(context)
                                .titleMedium
                                .override(
                                  fontFamily: 'OpenDyslexic',
                                  color: FlutterFlowTheme.of(context)
                                      .primaryBackground,
                                  letterSpacing: 0.0,
                                  useGoogleFonts: false,
                                ),
                            elevation: 4.0,
                            borderSide: const BorderSide(
                              color: Colors.transparent,
                              width: 1.0,
                            ),
                            borderRadius: BorderRadius.circular(12.0),
                          ),
                        ),
                      ),
                    ]
                        .divide(const SizedBox(height: 24.0))
                        .addToEnd(const SizedBox(height: 32.0)),
                  ),
                ),
              );
            },
          ),
        ),
      ),
    );
  }
}
