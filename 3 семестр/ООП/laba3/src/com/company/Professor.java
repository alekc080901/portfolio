package com.company;

import java.util.*;

public class Professor {

    private final String NAME;
    private final Subject subject;
    private final Queue<Student> examQueue = new LinkedList<Student>();
    private final PriorityQueue<Student> retakeQueue = new PriorityQueue<Student>(new StudentComparator());
    private final HashMap<Student, Integer> passedStudents = new HashMap<Student, Integer>();

    public Professor(String professorName, Subject subject, Deanery deanery) {
        this.NAME = professorName;
        this.subject = subject;
        deanery.addSubject(subject, this);
    }

    public void formExamQueue(Deanery deanery) {
            HashSet<Student> students = deanery.getStudents();
            Collections.shuffle(Arrays.asList(students.toArray()));
            examQueue.addAll(students);
        }

    public boolean giveMark(Student student) {
        Random markChoice = new Random();
        int mark = markChoice.nextInt(4) + 2;
        student.passExam(subject, mark);
        System.out.printf("Студент %s сдал на %d\n", student.getNAME(), mark);

        if (student.getExamsResult().get(subject) <= 2) {
            retakeQueue.add(student);
            return false;
        }
        else {
            passedStudents.put(student, mark);
            return true;
        }
    }

    public void startExam(Deanery deanery) {
        formExamQueue(deanery);

        for (Student s: examQueue) {
            giveMark(s);
        }
    }

    public void retakeExam(Deanery deanery) {
        if (retakeQueue.isEmpty()) {
            System.out.println("Студентов на пересдачу нет!");
        }

        ArrayList<Student> retakeArray = new ArrayList<Student>();
        while (!retakeQueue.isEmpty()) {
            Student s = retakeQueue.poll();
            if (!giveMark(s)) {
                retakeArray.add(s);
            }
            s.incrementRetakeNumber(subject);
            deanery.checkRetakeNumber(s, subject);
        }
        retakeQueue.addAll(retakeArray);
    }

    public String getNAME() {
        return NAME;
    }

    public Queue<Student> getFailedStudents() {
        return retakeQueue;
    }

    public HashMap<Student, Integer> getPassedStudents() {
        return passedStudents;
    }
}

class StudentComparator implements Comparator<Student>{

    public int compare(Student s1, Student s2) {
        if (s1.getNAME().compareTo(s2.getNAME()) < 0)
            return 1;
        else if (s1.getNAME().compareTo(s2.getNAME()) > 0)
            return -1;
        return 0;
    }
}
