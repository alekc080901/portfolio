package com.company;

public class Teacher extends LibraryVisitors {

    public Teacher(String surname, Book firstBook) {
        super(surname, firstBook);
    }

    @Override
    public void printBooks() {
        System.out.println("Я взял так много для студентов.");
    }
}
