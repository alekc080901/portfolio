package com.company;

public class Book {

    private final String TITLE;
    private final String AUTHOR;
    private final Library LIBRARY;

    public Book (String title, String author, Library lib) {
        this.TITLE = title;
        this.AUTHOR = author;
        this.LIBRARY = lib;
        lib.addBook(this);
    }

    public String getTITLE() {
        return TITLE;
    }

    public Library getLIBRARY() {
        return LIBRARY;
    }

    @Override
    public String toString() {
        return TITLE + " (" + AUTHOR + ")";
    }
}
