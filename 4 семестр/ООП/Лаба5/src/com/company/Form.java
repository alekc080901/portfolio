package com.company;

import java.util.ArrayList;
import java.util.List;

public class Form {
    private List<Question> questionList = new ArrayList<>();

    public List<Question> getQuestionList() {
        return questionList;
    }

    public void setQuestionList(List<Question> questionList) {
        this.questionList = questionList;
    }

    @Override
    public String toString() {
        StringBuilder string = new StringBuilder();
        for (int i = 0; i < questionList.size(); i++) {
            Question question = questionList.get(i);
            string.append(String.format("%d. %s\n%s\n%s", i + 1, question.getText(), question.getAnswer(),
                    question.isRequired() ? "Обязательный\n" : "Необязательный\n"));
        }
        return string.toString();
    }
}


