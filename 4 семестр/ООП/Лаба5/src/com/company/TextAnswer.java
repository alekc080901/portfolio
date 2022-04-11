package com.company;

public class TextAnswer extends Answer {
    private String text;

    public TextAnswer(String text) {
        this.text = text;
    }

    @Override
    public String toString() {
        return text;
    }

    public void setText(String text) {
        this.text = text;
    }
}
