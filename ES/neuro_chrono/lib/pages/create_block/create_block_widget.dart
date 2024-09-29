import '/auth/firebase_auth/auth_util.dart';
import '/backend/backend.dart';
import '/backend/schema/enums/enums.dart';
import '/flutter_flow/flutter_flow_drop_down.dart';
import '/flutter_flow/flutter_flow_icon_button.dart';
import '/flutter_flow/flutter_flow_theme.dart';
import '/flutter_flow/flutter_flow_util.dart';
import '/flutter_flow/flutter_flow_widgets.dart';
import '/flutter_flow/form_field_controller.dart';
import '/flutter_flow/custom_functions.dart' as functions;
import 'package:collection/collection.dart';
import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'create_block_model.dart';
export 'create_block_model.dart';

class CreateBlockWidget extends StatefulWidget {
  const CreateBlockWidget({super.key});

  @override
  State<CreateBlockWidget> createState() => _CreateBlockWidgetState();
}

class _CreateBlockWidgetState extends State<CreateBlockWidget> {
  late CreateBlockModel _model;

  final scaffoldKey = GlobalKey<ScaffoldState>();

  @override
  void initState() {
    super.initState();
    _model = createModel(context, () => CreateBlockModel());

    _model.blockDurationTextController ??= TextEditingController();
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
                'Create a new Block',
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
                          _model.blockTypeValue ??= 'Custom',
                        ),
                        options: formBlockTypesRecordList
                            .map((e) => valueOrDefault<String>(
                                  e.name,
                                  'Custom',
                                ))
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
                      FFButtonWidget(
                        onPressed: () async {
                          final datePickedTime = await showTimePicker(
                            context: context,
                            initialTime:
                                TimeOfDay.fromDateTime(getCurrentTimestamp),
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
                                getCurrentTimestamp.year,
                                getCurrentTimestamp.month,
                                getCurrentTimestamp.day,
                                datePickedTime.hour,
                                datePickedTime.minute,
                              );
                            });
                          }
                        },
                        text:
                            'Starting Time: ${functions.timeToString(functions.dateTimeToInt(_model.datePicked != null ? _model.datePicked! : getCurrentTimestamp))}',
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
                          labelText: 'Block Duration (min)',
                          labelStyle:
                              FlutterFlowTheme.of(context).labelLarge.override(
                                    fontFamily: 'OpenDyslexic',
                                    letterSpacing: 0.0,
                                    useGoogleFonts: false,
                                  ),
                          alignLabelWithHint: true,
                          hintStyle:
                              FlutterFlowTheme.of(context).labelLarge.override(
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
                        textAlign: TextAlign.start,
                        keyboardType: TextInputType.number,
                        validator: _model.blockDurationTextControllerValidator
                            .asValidator(context),
                        inputFormatters: [
                          FilteringTextInputFormatter.allow(RegExp('[0-9]'))
                        ],
                      ),
                      GridView(
                        padding: const EdgeInsets.fromLTRB(
                          0,
                          0.0,
                          0,
                          0,
                        ),
                        gridDelegate: const SliverGridDelegateWithFixedCrossAxisCount(
                          crossAxisCount: 1,
                          crossAxisSpacing: 0.0,
                          mainAxisSpacing: 1.0,
                          childAspectRatio: 7.0,
                        ),
                        shrinkWrap: true,
                        scrollDirection: Axis.vertical,
                        children: [
                          Theme(
                            data: ThemeData(
                              checkboxTheme: const CheckboxThemeData(
                                visualDensity: VisualDensity.compact,
                                materialTapTargetSize:
                                    MaterialTapTargetSize.shrinkWrap,
                              ),
                              unselectedWidgetColor:
                                  FlutterFlowTheme.of(context).secondaryText,
                            ),
                            child: CheckboxListTile(
                              value: _model.sundayValue ??= false,
                              onChanged: (newValue) async {
                                setState(() => _model.sundayValue = newValue!);
                              },
                              title: Text(
                                'Sunday',
                                style: FlutterFlowTheme.of(context)
                                    .bodyLarge
                                    .override(
                                      fontFamily: 'OpenDyslexic',
                                      letterSpacing: 0.0,
                                      useGoogleFonts: false,
                                    ),
                              ),
                              tileColor: FlutterFlowTheme.of(context)
                                  .secondaryBackground,
                              activeColor: FlutterFlowTheme.of(context).primary,
                              checkColor: FlutterFlowTheme.of(context).info,
                              dense: false,
                              controlAffinity: ListTileControlAffinity.trailing,
                            ),
                          ),
                          Theme(
                            data: ThemeData(
                              checkboxTheme: const CheckboxThemeData(
                                visualDensity: VisualDensity.compact,
                                materialTapTargetSize:
                                    MaterialTapTargetSize.shrinkWrap,
                              ),
                              unselectedWidgetColor:
                                  FlutterFlowTheme.of(context).secondaryText,
                            ),
                            child: CheckboxListTile(
                              value: _model.mondayValue ??= false,
                              onChanged: (newValue) async {
                                setState(() => _model.mondayValue = newValue!);
                              },
                              title: Text(
                                'Monday',
                                style: FlutterFlowTheme.of(context)
                                    .bodyLarge
                                    .override(
                                      fontFamily: 'OpenDyslexic',
                                      letterSpacing: 0.0,
                                      useGoogleFonts: false,
                                    ),
                              ),
                              tileColor: FlutterFlowTheme.of(context)
                                  .secondaryBackground,
                              activeColor: FlutterFlowTheme.of(context).primary,
                              checkColor: FlutterFlowTheme.of(context).info,
                              dense: false,
                              controlAffinity: ListTileControlAffinity.trailing,
                            ),
                          ),
                          Theme(
                            data: ThemeData(
                              checkboxTheme: const CheckboxThemeData(
                                visualDensity: VisualDensity.compact,
                                materialTapTargetSize:
                                    MaterialTapTargetSize.shrinkWrap,
                              ),
                              unselectedWidgetColor:
                                  FlutterFlowTheme.of(context).secondaryText,
                            ),
                            child: CheckboxListTile(
                              value: _model.tuesdayValue ??= false,
                              onChanged: (newValue) async {
                                setState(() => _model.tuesdayValue = newValue!);
                              },
                              title: Text(
                                'Tuesday',
                                style: FlutterFlowTheme.of(context)
                                    .bodyLarge
                                    .override(
                                      fontFamily: 'OpenDyslexic',
                                      letterSpacing: 0.0,
                                      useGoogleFonts: false,
                                    ),
                              ),
                              tileColor: FlutterFlowTheme.of(context)
                                  .secondaryBackground,
                              activeColor: FlutterFlowTheme.of(context).primary,
                              checkColor: FlutterFlowTheme.of(context).info,
                              dense: false,
                              controlAffinity: ListTileControlAffinity.trailing,
                            ),
                          ),
                          Theme(
                            data: ThemeData(
                              checkboxTheme: const CheckboxThemeData(
                                visualDensity: VisualDensity.compact,
                                materialTapTargetSize:
                                    MaterialTapTargetSize.shrinkWrap,
                              ),
                              unselectedWidgetColor:
                                  FlutterFlowTheme.of(context).secondaryText,
                            ),
                            child: CheckboxListTile(
                              value: _model.wednesdayValue ??= false,
                              onChanged: (newValue) async {
                                setState(
                                    () => _model.wednesdayValue = newValue!);
                              },
                              title: Text(
                                'Wednesday',
                                style: FlutterFlowTheme.of(context)
                                    .bodyLarge
                                    .override(
                                      fontFamily: 'OpenDyslexic',
                                      letterSpacing: 0.0,
                                      useGoogleFonts: false,
                                    ),
                              ),
                              tileColor: FlutterFlowTheme.of(context)
                                  .secondaryBackground,
                              activeColor: FlutterFlowTheme.of(context).primary,
                              checkColor: FlutterFlowTheme.of(context).info,
                              dense: false,
                              controlAffinity: ListTileControlAffinity.trailing,
                            ),
                          ),
                          Theme(
                            data: ThemeData(
                              checkboxTheme: const CheckboxThemeData(
                                visualDensity: VisualDensity.compact,
                                materialTapTargetSize:
                                    MaterialTapTargetSize.shrinkWrap,
                              ),
                              unselectedWidgetColor:
                                  FlutterFlowTheme.of(context).secondaryText,
                            ),
                            child: CheckboxListTile(
                              value: _model.thursdayValue ??= false,
                              onChanged: (newValue) async {
                                setState(
                                    () => _model.thursdayValue = newValue!);
                              },
                              title: Text(
                                'Thursday',
                                style: FlutterFlowTheme.of(context)
                                    .bodyLarge
                                    .override(
                                      fontFamily: 'OpenDyslexic',
                                      letterSpacing: 0.0,
                                      useGoogleFonts: false,
                                    ),
                              ),
                              tileColor: FlutterFlowTheme.of(context)
                                  .secondaryBackground,
                              activeColor: FlutterFlowTheme.of(context).primary,
                              checkColor: FlutterFlowTheme.of(context).info,
                              dense: false,
                              controlAffinity: ListTileControlAffinity.trailing,
                            ),
                          ),
                          Theme(
                            data: ThemeData(
                              checkboxTheme: const CheckboxThemeData(
                                visualDensity: VisualDensity.compact,
                                materialTapTargetSize:
                                    MaterialTapTargetSize.shrinkWrap,
                              ),
                              unselectedWidgetColor:
                                  FlutterFlowTheme.of(context).secondaryText,
                            ),
                            child: CheckboxListTile(
                              value: _model.fridayValue ??= false,
                              onChanged: (newValue) async {
                                setState(() => _model.fridayValue = newValue!);
                              },
                              title: Text(
                                'Friday',
                                style: FlutterFlowTheme.of(context)
                                    .bodyLarge
                                    .override(
                                      fontFamily: 'OpenDyslexic',
                                      letterSpacing: 0.0,
                                      useGoogleFonts: false,
                                    ),
                              ),
                              tileColor: FlutterFlowTheme.of(context)
                                  .secondaryBackground,
                              activeColor: FlutterFlowTheme.of(context).primary,
                              checkColor: FlutterFlowTheme.of(context).info,
                              dense: false,
                              controlAffinity: ListTileControlAffinity.trailing,
                            ),
                          ),
                          Theme(
                            data: ThemeData(
                              checkboxTheme: const CheckboxThemeData(
                                visualDensity: VisualDensity.compact,
                                materialTapTargetSize:
                                    MaterialTapTargetSize.shrinkWrap,
                              ),
                              unselectedWidgetColor:
                                  FlutterFlowTheme.of(context).secondaryText,
                            ),
                            child: CheckboxListTile(
                              value: _model.saturdayValue ??= false,
                              onChanged: (newValue) async {
                                setState(
                                    () => _model.saturdayValue = newValue!);
                              },
                              title: Text(
                                'Saturday',
                                style: FlutterFlowTheme.of(context)
                                    .bodyLarge
                                    .override(
                                      fontFamily: 'OpenDyslexic',
                                      letterSpacing: 0.0,
                                      useGoogleFonts: false,
                                    ),
                              ),
                              tileColor: FlutterFlowTheme.of(context)
                                  .secondaryBackground,
                              activeColor: FlutterFlowTheme.of(context).primary,
                              checkColor: FlutterFlowTheme.of(context).info,
                              dense: false,
                              controlAffinity: ListTileControlAffinity.trailing,
                            ),
                          ),
                        ],
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
                                if (!((_model.sundayValue! && functions.doesIntercept(buttonBlocksRecordList.toList(), functions.dateTimeToInt(_model.datePicked!), int.parse(_model.blockDurationTextController.text), WeekDay.Sunday)) ||
                                    (_model.mondayValue! &&
                                        functions.doesIntercept(
                                            buttonBlocksRecordList.toList(),
                                            functions.dateTimeToInt(
                                                _model.datePicked!),
                                            int.parse(_model
                                                .blockDurationTextController
                                                .text),
                                            WeekDay.Monday)) ||
                                    (_model.tuesdayValue! &&
                                        functions.doesIntercept(
                                            buttonBlocksRecordList.toList(),
                                            functions.dateTimeToInt(
                                                _model.datePicked!),
                                            int.parse(_model
                                                .blockDurationTextController
                                                .text),
                                            WeekDay.Tuesday)) ||
                                    (_model.wednesdayValue! &&
                                        functions.doesIntercept(
                                            buttonBlocksRecordList.toList(),
                                            functions.dateTimeToInt(_model.datePicked!),
                                            int.parse(_model.blockDurationTextController.text),
                                            WeekDay.Wednesday)) ||
                                    (_model.thursdayValue! && functions.doesIntercept(buttonBlocksRecordList.toList(), functions.dateTimeToInt(_model.datePicked!), int.parse(_model.blockDurationTextController.text), WeekDay.Thursday)) ||
                                    (_model.fridayValue! && functions.doesIntercept(buttonBlocksRecordList.toList(), functions.dateTimeToInt(_model.datePicked!), int.parse(_model.blockDurationTextController.text), WeekDay.Friday)) ||
                                    (_model.saturdayValue! && functions.doesIntercept(buttonBlocksRecordList.toList(), functions.dateTimeToInt(_model.datePicked!), int.parse(_model.blockDurationTextController.text), WeekDay.Saturday)))) {
                                  _model.selectedBlockType =
                                      await queryBlockTypesRecordOnce(
                                    queryBuilder: (blockTypesRecord) =>
                                        blockTypesRecord.where(
                                      'name',
                                      isEqualTo: _model.blockTypeValue,
                                    ),
                                    singleRecord: true,
                                  ).then((s) => s.firstOrNull);
                                  if (_model.sundayValue == true) {
                                    await BlocksRecord.collection
                                        .doc()
                                        .set(createBlocksRecordData(
                                          weekDay: WeekDay.Sunday,
                                          duration: int.tryParse(_model
                                              .blockDurationTextController
                                              .text),
                                          userId: currentUserUid,
                                          start: _model.datePicked != null
                                              ? functions.dateTimeToInt(
                                                  _model.datePicked!)
                                              : functions.dateTimeToInt(
                                                  getCurrentTimestamp),
                                          type: _model
                                              .selectedBlockType?.reference,
                                        ));
                                  }
                                  if (_model.mondayValue == true) {
                                    await BlocksRecord.collection
                                        .doc()
                                        .set(createBlocksRecordData(
                                          weekDay: WeekDay.Monday,
                                          duration: int.tryParse(_model
                                              .blockDurationTextController
                                              .text),
                                          userId: currentUserUid,
                                          start: _model.datePicked != null
                                              ? functions.dateTimeToInt(
                                                  _model.datePicked!)
                                              : functions.dateTimeToInt(
                                                  getCurrentTimestamp),
                                          type: _model
                                              .selectedBlockType?.reference,
                                        ));
                                  }
                                  if (_model.tuesdayValue == true) {
                                    await BlocksRecord.collection
                                        .doc()
                                        .set(createBlocksRecordData(
                                          weekDay: WeekDay.Tuesday,
                                          duration: int.tryParse(_model
                                              .blockDurationTextController
                                              .text),
                                          userId: currentUserUid,
                                          start: _model.datePicked != null
                                              ? functions.dateTimeToInt(
                                                  _model.datePicked!)
                                              : functions.dateTimeToInt(
                                                  getCurrentTimestamp),
                                          type: _model
                                              .selectedBlockType?.reference,
                                        ));
                                  }
                                  if (_model.wednesdayValue == true) {
                                    await BlocksRecord.collection
                                        .doc()
                                        .set(createBlocksRecordData(
                                          weekDay: WeekDay.Wednesday,
                                          duration: int.tryParse(_model
                                              .blockDurationTextController
                                              .text),
                                          userId: currentUserUid,
                                          start: _model.datePicked != null
                                              ? functions.dateTimeToInt(
                                                  _model.datePicked!)
                                              : functions.dateTimeToInt(
                                                  getCurrentTimestamp),
                                          type: _model
                                              .selectedBlockType?.reference,
                                        ));
                                  }
                                  if (_model.thursdayValue == true) {
                                    await BlocksRecord.collection
                                        .doc()
                                        .set(createBlocksRecordData(
                                          weekDay: WeekDay.Thursday,
                                          duration: int.tryParse(_model
                                              .blockDurationTextController
                                              .text),
                                          userId: currentUserUid,
                                          start: _model.datePicked != null
                                              ? functions.dateTimeToInt(
                                                  _model.datePicked!)
                                              : functions.dateTimeToInt(
                                                  getCurrentTimestamp),
                                          type: _model
                                              .selectedBlockType?.reference,
                                        ));
                                  }
                                  if (_model.fridayValue == true) {
                                    await BlocksRecord.collection
                                        .doc()
                                        .set(createBlocksRecordData(
                                          weekDay: WeekDay.Friday,
                                          duration: int.tryParse(_model
                                              .blockDurationTextController
                                              .text),
                                          userId: currentUserUid,
                                          start: _model.datePicked != null
                                              ? functions.dateTimeToInt(
                                                  _model.datePicked!)
                                              : functions.dateTimeToInt(
                                                  getCurrentTimestamp),
                                          type: _model
                                              .selectedBlockType?.reference,
                                        ));
                                  }
                                  if (_model.saturdayValue == true) {
                                    await BlocksRecord.collection
                                        .doc()
                                        .set(createBlocksRecordData(
                                          weekDay: WeekDay.Saturday,
                                          duration: int.tryParse(_model
                                              .blockDurationTextController
                                              .text),
                                          userId: currentUserUid,
                                          start: _model.datePicked != null
                                              ? functions.dateTimeToInt(
                                                  _model.datePicked!)
                                              : functions.dateTimeToInt(
                                                  getCurrentTimestamp),
                                          type: _model
                                              .selectedBlockType?.reference,
                                        ));
                                  }
                                  context.safePop();
                                } else {
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
                                }

                                setState(() {});
                              },
                              text: 'Create',
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
