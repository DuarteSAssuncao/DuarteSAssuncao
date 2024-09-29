import '/auth/firebase_auth/auth_util.dart';
import '/backend/backend.dart';
import '/backend/schema/enums/enums.dart';
import '/components/block_widget.dart';
import '/flutter_flow/flutter_flow_icon_button.dart';
import '/flutter_flow/flutter_flow_theme.dart';
import '/flutter_flow/flutter_flow_util.dart';
import '/actions/actions.dart' as action_blocks;
import '/flutter_flow/custom_functions.dart' as functions;
import 'package:auto_size_text/auto_size_text.dart';
import 'package:flutter/material.dart';
import 'package:flutter/scheduler.dart';
import 'planner_page_model.dart';
export 'planner_page_model.dart';

class PlannerPageWidget extends StatefulWidget {
  const PlannerPageWidget({super.key});

  @override
  State<PlannerPageWidget> createState() => _PlannerPageWidgetState();
}

class _PlannerPageWidgetState extends State<PlannerPageWidget>
    with TickerProviderStateMixin {
  late PlannerPageModel _model;

  final scaffoldKey = GlobalKey<ScaffoldState>();

  @override
  void initState() {
    super.initState();
    _model = createModel(context, () => PlannerPageModel());

    // On page load action.
    SchedulerBinding.instance.addPostFrameCallback((_) async {
      await action_blocks.notificationLoop(context);
    });

    _model.tabBarController = TabController(
      vsync: this,
      length: 7,
      initialIndex: min(
          valueOrDefault<int>(
            DateTime.now().weekday - 1,
            0,
          ),
          6),
    )..addListener(() => setState(() {}));
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
        backgroundColor: FlutterFlowTheme.of(context).primaryBackground,
        floatingActionButton: Padding(
          padding: const EdgeInsetsDirectional.fromSTEB(0.0, 0.0, 0.0, 40.0),
          child: FloatingActionButton(
            onPressed: () {
              print('FloatingActionButton pressed ...');
            },
            backgroundColor: FlutterFlowTheme.of(context).primary,
            elevation: 8.0,
            child: Align(
              alignment: const AlignmentDirectional(1.0, 1.0),
              child: FlutterFlowIconButton(
                borderColor: FlutterFlowTheme.of(context).primary,
                borderRadius: 20.0,
                borderWidth: 0.0,
                buttonSize: 55.0,
                fillColor: FlutterFlowTheme.of(context).primary,
                icon: Icon(
                  Icons.add,
                  color: FlutterFlowTheme.of(context).secondaryBackground,
                  size: 25.0,
                ),
                onPressed: () async {
                  context.pushNamed(
                    'CreateBlock',
                    extra: <String, dynamic>{
                      kTransitionInfoKey: const TransitionInfo(
                        hasTransition: true,
                        transitionType: PageTransitionType.topToBottom,
                        duration: Duration(milliseconds: 500),
                      ),
                    },
                  );
                },
              ),
            ),
          ),
        ),
        appBar: AppBar(
          backgroundColor: FlutterFlowTheme.of(context).primary,
          automaticallyImplyLeading: false,
          title: Text(
            'NeuroChrono',
            style: FlutterFlowTheme.of(context).headlineMedium.override(
                  fontFamily: 'OpenDyslexic',
                  color: FlutterFlowTheme.of(context).secondaryBackground,
                  fontSize: 18.0,
                  letterSpacing: 0.0,
                  useGoogleFonts: false,
                ),
          ),
          actions: [
            Align(
              alignment: const AlignmentDirectional(0.0, 0.0),
              child: Padding(
                padding: const EdgeInsetsDirectional.fromSTEB(0.0, 0.0, 15.0, 0.0),
                child: AutoSizeText(
                  dateTimeFormat(
                    'E, MMM d',
                    getCurrentTimestamp,
                    locale: FFLocalizations.of(context).languageCode,
                  ),
                  textAlign: TextAlign.center,
                  style: FlutterFlowTheme.of(context).headlineMedium.override(
                        fontFamily: 'OpenDyslexic',
                        color: FlutterFlowTheme.of(context).secondaryBackground,
                        fontSize: 18.0,
                        letterSpacing: 0.0,
                        useGoogleFonts: false,
                      ),
                ),
              ),
            ),
          ],
          centerTitle: false,
          elevation: 2.0,
        ),
        body: SafeArea(
          top: true,
          child: Column(
            children: [
              Expanded(
                child: TabBarView(
                  controller: _model.tabBarController,
                  children: [
                    StreamBuilder<List<BlocksRecord>>(
                      stream: queryBlocksRecord(
                        queryBuilder: (blocksRecord) => blocksRecord
                            .where(
                              'weekDay',
                              isEqualTo: WeekDay.Monday.serialize(),
                            )
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
                        List<BlocksRecord> listViewBlocksRecordList =
                            snapshot.data!;
                        return ListView.builder(
                          padding: const EdgeInsets.fromLTRB(
                            0,
                            6.0,
                            0,
                            60.0,
                          ),
                          scrollDirection: Axis.vertical,
                          itemCount: listViewBlocksRecordList.length,
                          itemBuilder: (context, listViewIndex) {
                            final listViewBlocksRecord =
                                listViewBlocksRecordList[listViewIndex];
                            return Align(
                              alignment: const AlignmentDirectional(0.0, 0.0),
                              child: Container(
                                constraints: const BoxConstraints(
                                  minHeight: 45.0,
                                ),
                                decoration: BoxDecoration(
                                  color: (functions.dateTimeToInt(
                                                  getCurrentTimestamp) >=
                                              listViewBlocksRecord.start) &&
                                          (functions.dateTimeToInt(
                                                  getCurrentTimestamp) <=
                                              functions.calculateEndOfBlock(
                                                  listViewBlocksRecord.start,
                                                  listViewBlocksRecord
                                                      .duration)) &&
                                          (functions.getWeekDay(
                                                  getCurrentTimestamp) ==
                                              listViewBlocksRecord.weekDay)
                                      ? FlutterFlowTheme.of(context).primary
                                      : FlutterFlowTheme.of(context)
                                          .primaryBackground,
                                ),
                                child: wrapWithModel(
                                  model: _model.blockModels1.getModel(
                                    listViewBlocksRecord.reference.id,
                                    listViewIndex,
                                  ),
                                  updateCallback: () => setState(() {}),
                                  child: BlockWidget(
                                    key: Key(
                                      'Keyzvo_${listViewBlocksRecord.reference.id}',
                                    ),
                                    blockDoc: listViewBlocksRecord,
                                  ),
                                ),
                              ),
                            );
                          },
                        );
                      },
                    ),
                    StreamBuilder<List<BlocksRecord>>(
                      stream: queryBlocksRecord(
                        queryBuilder: (blocksRecord) => blocksRecord
                            .where(
                              'weekDay',
                              isEqualTo: WeekDay.Tuesday.serialize(),
                            )
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
                        List<BlocksRecord> listViewBlocksRecordList =
                            snapshot.data!;
                        return ListView.builder(
                          padding: const EdgeInsets.fromLTRB(
                            0,
                            6.0,
                            0,
                            60.0,
                          ),
                          scrollDirection: Axis.vertical,
                          itemCount: listViewBlocksRecordList.length,
                          itemBuilder: (context, listViewIndex) {
                            final listViewBlocksRecord =
                                listViewBlocksRecordList[listViewIndex];
                            return Align(
                              alignment: const AlignmentDirectional(0.0, 0.0),
                              child: Container(
                                constraints: const BoxConstraints(
                                  minHeight: 45.0,
                                ),
                                decoration: BoxDecoration(
                                  color: (functions.dateTimeToInt(
                                                  getCurrentTimestamp) >=
                                              listViewBlocksRecord.start) &&
                                          (functions.dateTimeToInt(
                                                  getCurrentTimestamp) <=
                                              functions.calculateEndOfBlock(
                                                  listViewBlocksRecord.start,
                                                  listViewBlocksRecord
                                                      .duration)) &&
                                          (functions.getWeekDay(
                                                  getCurrentTimestamp) ==
                                              listViewBlocksRecord.weekDay)
                                      ? FlutterFlowTheme.of(context).primary
                                      : FlutterFlowTheme.of(context)
                                          .primaryBackground,
                                ),
                                child: wrapWithModel(
                                  model: _model.blockModels2.getModel(
                                    listViewBlocksRecord.reference.id,
                                    listViewIndex,
                                  ),
                                  updateCallback: () => setState(() {}),
                                  child: BlockWidget(
                                    key: Key(
                                      'Keylws_${listViewBlocksRecord.reference.id}',
                                    ),
                                    blockDoc: listViewBlocksRecord,
                                  ),
                                ),
                              ),
                            );
                          },
                        );
                      },
                    ),
                    StreamBuilder<List<BlocksRecord>>(
                      stream: queryBlocksRecord(
                        queryBuilder: (blocksRecord) => blocksRecord
                            .where(
                              'weekDay',
                              isEqualTo: WeekDay.Wednesday.serialize(),
                            )
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
                        List<BlocksRecord> listViewBlocksRecordList =
                            snapshot.data!;
                        return ListView.builder(
                          padding: const EdgeInsets.fromLTRB(
                            0,
                            6.0,
                            0,
                            60.0,
                          ),
                          scrollDirection: Axis.vertical,
                          itemCount: listViewBlocksRecordList.length,
                          itemBuilder: (context, listViewIndex) {
                            final listViewBlocksRecord =
                                listViewBlocksRecordList[listViewIndex];
                            return Align(
                              alignment: const AlignmentDirectional(0.0, 0.0),
                              child: Container(
                                constraints: const BoxConstraints(
                                  minHeight: 45.0,
                                ),
                                decoration: const BoxDecoration(),
                                child: wrapWithModel(
                                  model: _model.blockModels3.getModel(
                                    listViewBlocksRecord.reference.id,
                                    listViewIndex,
                                  ),
                                  updateCallback: () => setState(() {}),
                                  child: BlockWidget(
                                    key: Key(
                                      'Key97u_${listViewBlocksRecord.reference.id}',
                                    ),
                                    blockDoc: listViewBlocksRecord,
                                  ),
                                ),
                              ),
                            );
                          },
                        );
                      },
                    ),
                    StreamBuilder<List<BlocksRecord>>(
                      stream: queryBlocksRecord(
                        queryBuilder: (blocksRecord) => blocksRecord
                            .where(
                              'weekDay',
                              isEqualTo: WeekDay.Thursday.serialize(),
                            )
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
                        List<BlocksRecord> listViewBlocksRecordList =
                            snapshot.data!;
                        return ListView.builder(
                          padding: const EdgeInsets.fromLTRB(
                            0,
                            6.0,
                            0,
                            60.0,
                          ),
                          scrollDirection: Axis.vertical,
                          itemCount: listViewBlocksRecordList.length,
                          itemBuilder: (context, listViewIndex) {
                            final listViewBlocksRecord =
                                listViewBlocksRecordList[listViewIndex];
                            return Align(
                              alignment: const AlignmentDirectional(0.0, 0.0),
                              child: Container(
                                constraints: const BoxConstraints(
                                  minHeight: 45.0,
                                ),
                                decoration: BoxDecoration(
                                  color: (functions.dateTimeToInt(
                                                  getCurrentTimestamp) >=
                                              listViewBlocksRecord.start) &&
                                          (functions.dateTimeToInt(
                                                  getCurrentTimestamp) <=
                                              functions.calculateEndOfBlock(
                                                  listViewBlocksRecord.start,
                                                  listViewBlocksRecord
                                                      .duration)) &&
                                          (functions.getWeekDay(
                                                  getCurrentTimestamp) ==
                                              listViewBlocksRecord.weekDay)
                                      ? FlutterFlowTheme.of(context).primary
                                      : FlutterFlowTheme.of(context)
                                          .primaryBackground,
                                ),
                                child: wrapWithModel(
                                  model: _model.blockModels4.getModel(
                                    listViewBlocksRecord.reference.id,
                                    listViewIndex,
                                  ),
                                  updateCallback: () => setState(() {}),
                                  child: BlockWidget(
                                    key: Key(
                                      'Keyp45_${listViewBlocksRecord.reference.id}',
                                    ),
                                    blockDoc: listViewBlocksRecord,
                                  ),
                                ),
                              ),
                            );
                          },
                        );
                      },
                    ),
                    StreamBuilder<List<BlocksRecord>>(
                      stream: queryBlocksRecord(
                        queryBuilder: (blocksRecord) => blocksRecord
                            .where(
                              'weekDay',
                              isEqualTo: WeekDay.Friday.serialize(),
                            )
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
                        List<BlocksRecord> listViewBlocksRecordList =
                            snapshot.data!;
                        return ListView.builder(
                          padding: const EdgeInsets.fromLTRB(
                            0,
                            6.0,
                            0,
                            60.0,
                          ),
                          scrollDirection: Axis.vertical,
                          itemCount: listViewBlocksRecordList.length,
                          itemBuilder: (context, listViewIndex) {
                            final listViewBlocksRecord =
                                listViewBlocksRecordList[listViewIndex];
                            return Align(
                              alignment: const AlignmentDirectional(0.0, 0.0),
                              child: StreamBuilder<BlockTypesRecord>(
                                stream: BlockTypesRecord.getDocument(
                                    listViewBlocksRecord.type!),
                                builder: (context, snapshot) {
                                  // Customize what your widget looks like when it's loading.
                                  if (!snapshot.hasData) {
                                    return Center(
                                      child: SizedBox(
                                        width: 50.0,
                                        height: 50.0,
                                        child: CircularProgressIndicator(
                                          valueColor:
                                              AlwaysStoppedAnimation<Color>(
                                            FlutterFlowTheme.of(context)
                                                .primary,
                                          ),
                                        ),
                                      ),
                                    );
                                  }
                                  final containerBlockTypesRecord =
                                      snapshot.data!;
                                  return Container(
                                    constraints: const BoxConstraints(
                                      minHeight: 45.0,
                                    ),
                                    decoration: BoxDecoration(
                                      color: (functions.dateTimeToInt(
                                                      getCurrentTimestamp) >=
                                                  listViewBlocksRecord.start) &&
                                              (functions.dateTimeToInt(
                                                      getCurrentTimestamp) <=
                                                  functions.calculateEndOfBlock(
                                                      listViewBlocksRecord
                                                          .start,
                                                      listViewBlocksRecord
                                                          .duration)) &&
                                              (functions.getWeekDay(
                                                      getCurrentTimestamp) ==
                                                  listViewBlocksRecord.weekDay)
                                          ? FlutterFlowTheme.of(context).primary
                                          : FlutterFlowTheme.of(context)
                                              .primaryBackground,
                                    ),
                                    child: Container(
                                      key: const ValueKey('block_vsc7'),
                                      child: wrapWithModel(
                                        model: _model.blockModels5.getModel(
                                          listViewBlocksRecord.reference.id,
                                          listViewIndex,
                                        ),
                                        updateCallback: () => setState(() {}),
                                        child: BlockWidget(
                                          key: Key(
                                            'Keyusp_${listViewBlocksRecord.reference.id}',
                                          ),
                                          blockDoc: listViewBlocksRecord,
                                        ),
                                      ),
                                    ),
                                  );
                                },
                              ),
                            );
                          },
                        );
                      },
                    ),
                    StreamBuilder<List<BlocksRecord>>(
                      stream: queryBlocksRecord(
                        queryBuilder: (blocksRecord) => blocksRecord
                            .where(
                              'weekDay',
                              isEqualTo: WeekDay.Saturday.serialize(),
                            )
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
                        List<BlocksRecord> listViewBlocksRecordList =
                            snapshot.data!;
                        return ListView.builder(
                          padding: const EdgeInsets.fromLTRB(
                            0,
                            6.0,
                            0,
                            60.0,
                          ),
                          scrollDirection: Axis.vertical,
                          itemCount: listViewBlocksRecordList.length,
                          itemBuilder: (context, listViewIndex) {
                            final listViewBlocksRecord =
                                listViewBlocksRecordList[listViewIndex];
                            return Align(
                              alignment: const AlignmentDirectional(0.0, 0.0),
                              child: StreamBuilder<BlockTypesRecord>(
                                stream: BlockTypesRecord.getDocument(
                                    listViewBlocksRecord.type!),
                                builder: (context, snapshot) {
                                  // Customize what your widget looks like when it's loading.
                                  if (!snapshot.hasData) {
                                    return Center(
                                      child: SizedBox(
                                        width: 50.0,
                                        height: 50.0,
                                        child: CircularProgressIndicator(
                                          valueColor:
                                              AlwaysStoppedAnimation<Color>(
                                            FlutterFlowTheme.of(context)
                                                .primary,
                                          ),
                                        ),
                                      ),
                                    );
                                  }
                                  final containerBlockTypesRecord =
                                      snapshot.data!;
                                  return Container(
                                    constraints: const BoxConstraints(
                                      minHeight: 45.0,
                                    ),
                                    decoration: BoxDecoration(
                                      color: (functions.dateTimeToInt(
                                                      getCurrentTimestamp) >=
                                                  listViewBlocksRecord.start) &&
                                              (functions.dateTimeToInt(
                                                      getCurrentTimestamp) <=
                                                  functions.calculateEndOfBlock(
                                                      listViewBlocksRecord
                                                          .start,
                                                      listViewBlocksRecord
                                                          .duration)) &&
                                              (functions.getWeekDay(
                                                      getCurrentTimestamp) ==
                                                  listViewBlocksRecord.weekDay)
                                          ? FlutterFlowTheme.of(context).primary
                                          : FlutterFlowTheme.of(context)
                                              .primaryBackground,
                                    ),
                                    child: wrapWithModel(
                                      model: _model.blockModels6.getModel(
                                        listViewBlocksRecord.reference.id,
                                        listViewIndex,
                                      ),
                                      updateCallback: () => setState(() {}),
                                      child: BlockWidget(
                                        key: Key(
                                          'Keyjs0_${listViewBlocksRecord.reference.id}',
                                        ),
                                        blockDoc: listViewBlocksRecord,
                                      ),
                                    ),
                                  );
                                },
                              ),
                            );
                          },
                        );
                      },
                    ),
                    StreamBuilder<List<BlocksRecord>>(
                      stream: queryBlocksRecord(
                        queryBuilder: (blocksRecord) => blocksRecord
                            .where(
                              'weekDay',
                              isEqualTo: WeekDay.Sunday.serialize(),
                            )
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
                        List<BlocksRecord> listViewBlocksRecordList =
                            snapshot.data!;
                        return ListView.builder(
                          padding: const EdgeInsets.fromLTRB(
                            0,
                            6.0,
                            0,
                            60.0,
                          ),
                          scrollDirection: Axis.vertical,
                          itemCount: listViewBlocksRecordList.length,
                          itemBuilder: (context, listViewIndex) {
                            final listViewBlocksRecord =
                                listViewBlocksRecordList[listViewIndex];
                            return Align(
                              alignment: const AlignmentDirectional(0.0, 0.0),
                              child: Container(
                                constraints: const BoxConstraints(
                                  minHeight: 45.0,
                                ),
                                decoration: BoxDecoration(
                                  color: (functions.dateTimeToInt(
                                                  getCurrentTimestamp) >=
                                              listViewBlocksRecord.start) &&
                                          (functions.dateTimeToInt(
                                                  getCurrentTimestamp) <=
                                              functions.calculateEndOfBlock(
                                                  listViewBlocksRecord.start,
                                                  listViewBlocksRecord
                                                      .duration)) &&
                                          (functions.getWeekDay(
                                                  getCurrentTimestamp) ==
                                              listViewBlocksRecord.weekDay)
                                      ? FlutterFlowTheme.of(context).primary
                                      : FlutterFlowTheme.of(context)
                                          .primaryBackground,
                                ),
                                child: wrapWithModel(
                                  model: _model.blockModels7.getModel(
                                    listViewBlocksRecord.reference.id,
                                    listViewIndex,
                                  ),
                                  updateCallback: () => setState(() {}),
                                  child: BlockWidget(
                                    key: Key(
                                      'Key5pc_${listViewBlocksRecord.reference.id}',
                                    ),
                                    blockDoc: listViewBlocksRecord,
                                  ),
                                ),
                              ),
                            );
                          },
                        );
                      },
                    ),
                  ],
                ),
              ),
              Align(
                alignment: const Alignment(0.0, 0),
                child: TabBar(
                  labelColor: FlutterFlowTheme.of(context).primaryText,
                  unselectedLabelColor:
                      FlutterFlowTheme.of(context).secondaryText,
                  labelStyle: FlutterFlowTheme.of(context).titleMedium.override(
                        fontFamily: 'OpenDyslexic',
                        letterSpacing: 0.0,
                        useGoogleFonts: false,
                      ),
                  unselectedLabelStyle:
                      FlutterFlowTheme.of(context).titleMedium.override(
                            fontFamily: 'OpenDyslexic',
                            letterSpacing: 0.0,
                            useGoogleFonts: false,
                          ),
                  indicatorColor: FlutterFlowTheme.of(context).primary,
                  indicatorWeight: 3.0,
                  tabs: const [
                    Tab(
                      text: 'M',
                    ),
                    Tab(
                      text: 'T',
                    ),
                    Tab(
                      text: 'W',
                    ),
                    Tab(
                      text: 'T',
                    ),
                    Tab(
                      key: ValueKey('Friday_zzb5'),
                      text: 'F',
                    ),
                    Tab(
                      text: 'S',
                    ),
                    Tab(
                      text: 'S',
                    ),
                  ],
                  controller: _model.tabBarController,
                  onTap: (i) async {
                    [
                      () async {},
                      () async {},
                      () async {},
                      () async {},
                      () async {},
                      () async {},
                      () async {}
                    ][i]();
                  },
                ),
              ),
            ],
          ),
        ),
      ),
    );
  }
}
