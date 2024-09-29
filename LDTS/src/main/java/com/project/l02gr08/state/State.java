package com.project.l02gr08.state;

import com.project.l02gr08.controller.Controller;
import com.project.l02gr08.viewer.Viewer;

public abstract class State<C extends Controller, V extends Viewer> {
    private C controller;
    private V viewer;

    public State(C controller, V viewer) {
        this.viewer = viewer;
        this.controller = controller;
    }

    public C getController() {
        return controller;
    }

    public V getViewer() {
        return viewer;
    }

    public void setController(C controller) {
        this.controller = controller;
    }

    public void setViewer(V viewer) {
        this.viewer = viewer;
    }
}
