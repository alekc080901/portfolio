package com.company;

public class Director extends Employee {

    Director(String name, String surname, int age, Sex s) {
        super(name, surname, age, s);
    }

    public void hireEmployee(Firm f, Employee e) {
        if (f.getDirector() == this) {
            f.getEmployees().add(e);
        }
    }

    public void fireEmployee(Firm f, Employee e) {
        if (f.getDirector() == this) {
            f.getEmployees().remove(e);
            System.out.printf("Сотрудник %s был уволен\n", this);
        }
    }
}
