package com.company;

import java.util.List;

public class InformationExpert {
    private final Form form = new Form();

    public void addQuestion(Question question) {
        List<Question> questionList = form.getQuestionList();
        questionList.add(question);
        form.setQuestionList(questionList);
    }

    public String getForm() {
        return form.toString();
    }
}
