package com.company;

import java.util.ArrayList;

public class Firm {
    private final String NAME;
    private Director director;
    private final ArrayList<Employee> Employees = new ArrayList<>();

    public Firm(String name, Director d) {
        this.NAME = name;
        this.director = d;
    }

    public void setDirector(Director director) {
        this.director = director;
    }

    public Director getDirector() {
        return director;
    }

    public ArrayList<Employee> getEmployees() {
        return Employees;
    }
}
