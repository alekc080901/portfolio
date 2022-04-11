package com.company;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Set;

public class Deanery {

    private final HashMap<Professor, Subject> subjectsMap = new HashMap<>();
    private final HashSet<Student> studentsList = new HashSet<Student>();

    public void addSubject(Subject subject, Professor professor) {
        subjectsMap.put(professor, subject);
    }

    public void addStudent(Student student) {
        studentsList.add(student);
    }

    public void checkRetakeNumber(Student student, Subject subject) {
        if (student.getRetakesNumber(subject) >= 3) {
            studentsList.remove(student);
            System.out.println("Студент" + student + " отчислен!");
        }
    }

    public HashSet<Student> getStudents() {
        return studentsList;
    }

    public Professor[] getProfessors() {
        Set<Professor> professorsSet = subjectsMap.keySet();
        return professorsSet.toArray(new Professor[0]);
    }
}
