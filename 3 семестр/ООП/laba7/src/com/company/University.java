package com.company;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class University {
    private final String title;
    private final List<UniversityConstruction> universityObjects = new ArrayList<>();

    public University(String title) {
        this.title = title;
    }

    public void addConstructions(UniversityConstruction ... constructions) {
        universityObjects.addAll(Arrays.asList(constructions));
    }

    public void showInfo() {
        System.out.println("Список университетских построек");

        for (UniversityConstruction construction : universityObjects) {
            System.out.println(construction);
        }
    }

    public String getTitle() {
        return title;
    }
}
