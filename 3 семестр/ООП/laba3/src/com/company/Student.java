package com.company;

import java.util.HashMap;

public class Student {

    private final String NAME;
    private final HashMap<Subject, Integer> examsResult = new HashMap<>();
    private final HashMap<Subject, Integer> retakesNumber = new HashMap<>();

    public Student(String studentName, Deanery deanery) {
        this.NAME = studentName;
        deanery.addStudent(this);
    }

    public String getNAME() {
        return NAME;
    }

    public void passExam(Subject subject, int mark) {
        examsResult.put(subject, mark);
    }

    public void incrementRetakeNumber(Subject subject) {
        retakesNumber.merge(subject, 1, Integer::sum);
    }

    public HashMap<Subject, Integer> getExamsResult() {
        return examsResult;
    }

    public int getRetakesNumber(Subject subject) {
        return retakesNumber.get(subject);
    }
}
