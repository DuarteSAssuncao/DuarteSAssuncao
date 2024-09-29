import '/backend/backend.dart';
import '/backend/schema/enums/enums.dart';
import '/components/task_item_widget.dart';
import '/flutter_flow/flutter_flow_icon_button.dart';
import '/flutter_flow/flutter_flow_theme.dart';
import '/flutter_flow/flutter_flow_util.dart';
import '/custom_code/actions/index.dart' as actions;
import '/flutter_flow/custom_functions.dart' as functions;
import 'package:flutter/material.dart';
import 'package:font_awesome_flutter/font_awesome_flutter.dart';
import 'block_view_model.dart';
export 'block_view_model.dart';

class BlockViewWidget extends StatefulWidget {
  const BlockViewWidget({
    super.key,
    required this.block,
  });

  final DocumentReference? block;

  @override
  State<BlockViewWidget> createState() => _BlockViewWidgetState();
}

class _BlockViewWidgetState extends State<BlockViewWidget> {
  late BlockViewModel _model;

  final scaffoldKey = GlobalKey<ScaffoldState>();

  @override
  void initState() {
    super.initState();
    _model = createModel(context, () => BlockViewModel());

    _model.newTaskTextController ??= TextEditingController();
    _model.newTaskFocusNode ??= FocusNode();
  }

  @override
  void dispose() {
    _model.dispose();

    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return StreamBuilder<BlocksRecord>(
      stream: BlocksRecord.getDocument(widget.block!),
      builder: (context, snapshot) {
        // Customize what your widget looks like when it's loading.
        if (!snapshot.hasData) {
          return Scaffold(
            backgroundColor: FlutterFlowTheme.of(context).secondaryBackground,
            body: Center(
              child: SizedBox(
                width: 50.0,
                height: 50.0,
                child: CircularProgressIndicator(
                  valueColor: AlwaysStoppedAnimation<Color>(
                    FlutterFlowTheme.of(context).primary,
                  ),
                ),
              ),
            ),
          );
        }
        final blockViewBlocksRecord = snapshot.data!;
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
                    'View Block',
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
              child: Padding(
                padding: const EdgeInsetsDirectional.fromSTEB(16.0, 12.0, 16.0, 0.0),
                child: Column(
                  mainAxisSize: MainAxisSize.max,
                  crossAxisAlignment: CrossAxisAlignment.start,
                  children: [
                    Padding(
                      padding:
                          const EdgeInsetsDirectional.fromSTEB(8.0, 0.0, 0.0, 0.0),
                      child: StreamBuilder<BlockTypesRecord>(
                        stream: BlockTypesRecord.getDocument(
                            blockViewBlocksRecord.type!),
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
                          final rowBlockTypesRecord = snapshot.data!;
                          return Row(
                            mainAxisSize: MainAxisSize.max,
                            mainAxisAlignment: MainAxisAlignment.spaceBetween,
                            children: [
                              Column(
                                mainAxisSize: MainAxisSize.max,
                                crossAxisAlignment: CrossAxisAlignment.start,
                                children: [
                                  Text(
                                    rowBlockTypesRecord.name,
                                    style: FlutterFlowTheme.of(context)
                                        .headlineMedium
                                        .override(
                                          fontFamily: 'OpenDyslexic',
                                          letterSpacing: 0.0,
                                          useGoogleFonts: false,
                                        ),
                                  ),
                                  Text(
                                    () {
                                      if (blockViewBlocksRecord.weekDay ==
                                          WeekDay.Monday) {
                                        return 'Monday';
                                      } else if (blockViewBlocksRecord
                                              .weekDay ==
                                          WeekDay.Tuesday) {
                                        return 'Tuesday';
                                      } else if (blockViewBlocksRecord
                                              .weekDay ==
                                          WeekDay.Wednesday) {
                                        return 'Wednesday';
                                      } else if (blockViewBlocksRecord
                                              .weekDay ==
                                          WeekDay.Thursday) {
                                        return 'Thursday';
                                      } else if (blockViewBlocksRecord
                                              .weekDay ==
                                          WeekDay.Friday) {
                                        return 'Friday';
                                      } else if (blockViewBlocksRecord
                                              .weekDay ==
                                          WeekDay.Saturday) {
                                        return 'Saturday';
                                      } else {
                                        return 'Sunday';
                                      }
                                    }(),
                                    style: FlutterFlowTheme.of(context)
                                        .bodyLarge
                                        .override(
                                          fontFamily: 'OpenDyslexic',
                                          letterSpacing: 0.0,
                                          useGoogleFonts: false,
                                        ),
                                  ),
                                  Text(
                                    'start: ${functions.timeToString(blockViewBlocksRecord.start)}',
                                    style: FlutterFlowTheme.of(context)
                                        .bodyLarge
                                        .override(
                                          fontFamily: 'OpenDyslexic',
                                          letterSpacing: 0.0,
                                          useGoogleFonts: false,
                                        ),
                                  ),
                                  Text(
                                    'end: ${functions.timeToString(functions.calculateEndOfBlock(blockViewBlocksRecord.start, blockViewBlocksRecord.duration))}',
                                    style: FlutterFlowTheme.of(context)
                                        .bodyLarge
                                        .override(
                                          fontFamily: 'OpenDyslexic',
                                          letterSpacing: 0.0,
                                          useGoogleFonts: false,
                                        ),
                                  ),
                                  Text(
                                    'duration: ${blockViewBlocksRecord.duration.toString()} min',
                                    style: FlutterFlowTheme.of(context)
                                        .bodyLarge
                                        .override(
                                          fontFamily: 'OpenDyslexic',
                                          letterSpacing: 0.0,
                                          useGoogleFonts: false,
                                        ),
                                  ),
                                ],
                              ),
                              FlutterFlowIconButton(
                                borderColor:
                                    FlutterFlowTheme.of(context).primary,
                                borderRadius: 20.0,
                                borderWidth: 2.0,
                                buttonSize: 55.0,
                                fillColor: FlutterFlowTheme.of(context).primary,
                                icon: FaIcon(
                                  FontAwesomeIcons.pen,
                                  color: FlutterFlowTheme.of(context).info,
                                  size: 20.0,
                                ),
                                onPressed: () async {
                                  context.pushNamed(
                                    'EditBlock',
                                    queryParameters: {
                                      'type': serializeParam(
                                        rowBlockTypesRecord,
                                        ParamType.Document,
                                      ),
                                      'day': serializeParam(
                                        blockViewBlocksRecord.weekDay,
                                        ParamType.Enum,
                                      ),
                                      'startingTime': serializeParam(
                                        blockViewBlocksRecord.start,
                                        ParamType.int,
                                      ),
                                      'duration': serializeParam(
                                        blockViewBlocksRecord.duration,
                                        ParamType.int,
                                      ),
                                      'block': serializeParam(
                                        blockViewBlocksRecord,
                                        ParamType.Document,
                                      ),
                                      'tasks': serializeParam(
                                        blockViewBlocksRecord.tasks,
                                        ParamType.String,
                                        true,
                                      ),
                                    }.withoutNulls,
                                    extra: <String, dynamic>{
                                      'type': rowBlockTypesRecord,
                                      'block': blockViewBlocksRecord,
                                      kTransitionInfoKey: const TransitionInfo(
                                        hasTransition: true,
                                        transitionType:
                                            PageTransitionType.topToBottom,
                                        duration: Duration(milliseconds: 500),
                                      ),
                                    },
                                  );
                                },
                              ),
                            ],
                          );
                        },
                      ),
                    ),
                    Flexible(
                      child: Builder(
                        builder: (context) {
                          final taskList = blockViewBlocksRecord.tasks.toList();
                          return ReorderableListView.builder(
                            padding: EdgeInsets.zero,
                            primary: false,
                            scrollDirection: Axis.vertical,
                            itemCount: taskList.length,
                            itemBuilder: (context, taskListIndex) {
                              final taskListItem = taskList[taskListIndex];
                              return Container(
                                key: ValueKey("ListView_c3imziwn" '_' +
                                    taskListIndex.toString()),
                                child: Card(
                                  clipBehavior: Clip.antiAliasWithSaveLayer,
                                  color: FlutterFlowTheme.of(context)
                                      .secondaryBackground,
                                  elevation: 4.0,
                                  shape: RoundedRectangleBorder(
                                    borderRadius: BorderRadius.circular(12.0),
                                  ),
                                  child: TaskItemWidget(
                                    key: Key(
                                        'Keyj6q_${taskListIndex}_of_${taskList.length}'),
                                    task: taskListItem,
                                    blockDoc: blockViewBlocksRecord.reference,
                                  ),
                                ),
                              );
                            },
                            onReorder: (int reorderableOldIndex,
                                int reorderableNewIndex) async {
                              _model.updatedTasks = await actions.taskMove(
                                blockViewBlocksRecord.tasks.toList(),
                                reorderableOldIndex,
                                reorderableNewIndex,
                              );

                              await blockViewBlocksRecord.reference.update({
                                ...mapToFirestore(
                                  {
                                    'tasks': _model.updatedTasks,
                                  },
                                ),
                              });

                              setState(() {});
                            },
                          );
                        },
                      ),
                    ),
                    Row(
                      mainAxisSize: MainAxisSize.max,
                      mainAxisAlignment: MainAxisAlignment.spaceBetween,
                      children: [
                        Expanded(
                          child: TextFormField(
                            controller: _model.newTaskTextController,
                            focusNode: _model.newTaskFocusNode,
                            autofocus: true,
                            obscureText: false,
                            decoration: InputDecoration(
                              isDense: true,
                              labelText: 'New Task',
                              labelStyle: FlutterFlowTheme.of(context)
                                  .labelLarge
                                  .override(
                                    fontFamily: 'OpenDyslexic',
                                    letterSpacing: 0.0,
                                    useGoogleFonts: false,
                                  ),
                              hintStyle: FlutterFlowTheme.of(context)
                                  .labelLarge
                                  .override(
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
                            style:
                                FlutterFlowTheme.of(context).bodyLarge.override(
                                      fontFamily: 'OpenDyslexic',
                                      fontSize: 20.0,
                                      letterSpacing: 0.0,
                                      useGoogleFonts: false,
                                    ),
                            validator: _model.newTaskTextControllerValidator
                                .asValidator(context),
                          ),
                        ),
                        Padding(
                          padding: const EdgeInsetsDirectional.fromSTEB(
                              8.0, 0.0, 0.0, 0.0),
                          child: FlutterFlowIconButton(
                            borderColor: FlutterFlowTheme.of(context).primary,
                            borderRadius: 20.0,
                            borderWidth: 2.0,
                            buttonSize: 55.0,
                            fillColor: FlutterFlowTheme.of(context).primary,
                            icon: const Icon(
                              Icons.add,
                              color: Colors.white,
                              size: 25.0,
                            ),
                            onPressed: () async {
                              if (_model.newTaskTextController.text != '') {
                                if (blockViewBlocksRecord.tasks.contains(
                                    _model.newTaskTextController.text)) {
                                  // Error Message
                                  ScaffoldMessenger.of(context)
                                      .clearSnackBars();
                                  ScaffoldMessenger.of(context).showSnackBar(
                                    SnackBar(
                                      content: Text(
                                        'That task already exists!',
                                        style: TextStyle(
                                          color:
                                              FlutterFlowTheme.of(context).info,
                                          fontSize: 20.0,
                                        ),
                                      ),
                                      duration: const Duration(milliseconds: 3000),
                                      backgroundColor:
                                          FlutterFlowTheme.of(context).error,
                                    ),
                                  );
                                } else {
                                  // Add Task

                                  await blockViewBlocksRecord.reference.update({
                                    ...mapToFirestore(
                                      {
                                        'tasks': FieldValue.arrayUnion([
                                          _model.newTaskTextController.text
                                        ]),
                                      },
                                    ),
                                  });
                                  setState(() {
                                    _model.newTaskTextController?.clear();
                                  });
                                  // Success Message
                                  ScaffoldMessenger.of(context)
                                      .clearSnackBars();
                                  ScaffoldMessenger.of(context).showSnackBar(
                                    SnackBar(
                                      content: Text(
                                        'Task successfully added!',
                                        style: TextStyle(
                                          color: FlutterFlowTheme.of(context)
                                              .primaryBackground,
                                          fontSize: 20.0,
                                        ),
                                      ),
                                      duration: const Duration(milliseconds: 3000),
                                      backgroundColor:
                                          FlutterFlowTheme.of(context).success,
                                    ),
                                  );
                                }
                              }
                            },
                          ),
                        ),
                      ],
                    ),
                  ]
                      .divide(const SizedBox(height: 12.0))
                      .addToEnd(const SizedBox(height: 32.0)),
                ),
              ),
            ),
          ),
        );
      },
    );
  }
}
