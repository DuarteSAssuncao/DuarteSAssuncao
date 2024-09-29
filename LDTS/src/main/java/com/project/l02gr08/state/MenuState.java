package com.project.l02gr08.state;

import com.project.l02gr08.Game;
import com.project.l02gr08.controller.HelpController;
import com.project.l02gr08.controller.MenuController;
import com.project.l02gr08.controller.gamecontroller.WhiteChoiceController;
import com.project.l02gr08.state.gamestate.ChoiceState;
import com.project.l02gr08.viewer.HelpViewer;
import com.project.l02gr08.viewer.MenuViewer;
import com.project.l02gr08.viewer.gameviewer.ChoiceViewer;

import java.util.List;

public class MenuState extends State<MenuController, MenuViewer> {
    private int selection = 0;
    private final List<String> entries;

    enum Action {
        Start,
        Help,
        Quit,
    }

    private final List<Action> actions;

    public int getSelection() {
        return selection;
    }

    public void setSelection(int sel) {
        if (sel < 0)
            sel = entries.size() + sel;
        selection = sel % entries.size();
    }

    public List<String> getEntries() {
        return entries;
    }

    public void selAction(Game g) {
        switch (actions.get(selection)) {
            case Start:
                g.setState(new ChoiceState(new WhiteChoiceController(), new ChoiceViewer()));
                return;
            case Quit:
                g.setState(null);
                return;
            case Help:
                g.setState(new HelpState(new HelpController(), new HelpViewer()));
        }
    }

    public MenuState(MenuController C, MenuViewer V) {
        super(C, V);
        entries = List.of("Start Game", "Help/Rules", "Quit");
        actions = List.of(Action.Start, Action.Help, Action.Quit);
    }

}
