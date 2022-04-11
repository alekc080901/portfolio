package com.company;

public class Student extends LibraryVisitors {

    public Student(String surname, Book firstBook) {
        super(surname, firstBook);
    }

    @Override
    public void printBooks() {
        if (getBooks().isEmpty())
            System.out.println("Никаких книг нет.");
        else
            System.out.println(getBooks());
    }
}
