package ru.nikitin.server.controllers;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;

@Controller
public class RouteController {

    @GetMapping("/")
    public String main_redirect() {
        return "redirect:/stationery/home";
    }

}
