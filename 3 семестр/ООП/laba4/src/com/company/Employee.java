package com.company;

public class Employee {
    private final String NAME;
    private final String SURNAME;
    private final Sex sex;
    private int age;

    public Employee(String name, String surname, int age, Sex s) {
        this.NAME = name;
        this.SURNAME = surname;
        this.age = age;
        this.sex = s;
    }

    public void resign(Firm f) {
        f.getEmployees().remove(this);
        System.out.printf("Сотрудник %s уволился\n", this);
    }

    public void retire(Firm f) {
        if ((this.age > 65 && this.sex == Sex.Male) || (this.age > 60 && this.sex == Sex.Female)) {
            f.getEmployees().remove(this);
            System.out.printf("Сотрудник %s вышел на пенсию (возраст %d)\n", this, this.age);
        }
        else
            System.out.printf("Сотрудник %s не вышел на пенсию (возраст %d)\n", this, this.age);
    }

    @Override
    public String toString() {
        return NAME + " " + SURNAME;
    }
}
