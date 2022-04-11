package com.company;

public class Question {
    private String text;
    private QuestionTypes type;
    private Answer answer;
    private boolean isRequired;

    public Question(String text, QuestionTypes type, Answer answer, boolean isRequired) {
        this.text = text;
        this.type = type;
        this.answer = answer;
        this.isRequired = isRequired;
    }

    public String getText() {
        return text;
    }

    public Answer getAnswer() {
        return answer;
    }

    public boolean isRequired() {
        return isRequired;
    }
}
