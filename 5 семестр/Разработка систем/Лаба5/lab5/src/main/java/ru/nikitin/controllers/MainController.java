package ru.nikitin.controllers;

import lombok.Data;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.context.ApplicationContext;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.ui.ModelMap;
import org.springframework.validation.BindingResult;
import org.springframework.web.bind.annotation.*;
import ru.nikitin.entities.Stationery;
import ru.nikitin.services.UserService;
import ru.nikitin.services.impl.StationeryServiceImpl;

import javax.validation.Valid;

@Controller
public @Data
class MainController {
    private final PasswordEncoder passwordEncoder;
    private final ApplicationContext context;
    private final StationeryServiceImpl stationeryService;
    private final UserService userService;

    @Autowired
    public MainController(@Qualifier("passwordEncoder") PasswordEncoder passwordEncoder,
                          @Qualifier("userServiceImpl") UserService userService,
                          ApplicationContext applicationContext) {
        this.passwordEncoder = passwordEncoder;
        this.context = applicationContext;
        this.userService = userService;
        this.stationeryService = context.getBean("stationeryServiceImpl", StationeryServiceImpl.class);
    }

    @GetMapping("/")
    public String homeRedirect() {
        return "redirect:/home";
    }

    @GetMapping("/home")
    public String mainPage(Model model) {
        model.addAttribute("stationery", stationeryService.getAll());
        return "home";
    }

    @GetMapping("/add")
    public String addPage(Model model) {
        model.addAttribute("stationery", new Stationery());
        return "add";
    }
    @PostMapping("/add")
    public String addFormHandler(@ModelAttribute("stationery") Stationery stationery) {
        stationeryService.add(stationery);
        return "redirect:/home";
    }

    @GetMapping("/edit")
    public String editPage(Model model) {
        model.addAttribute("stationery", new Stationery());
        return "edit";
    }
    @PostMapping("/edit")
    public String editFormHandler(
            @ModelAttribute @Valid Stationery stationery,
            BindingResult bindingResult,
            @RequestParam("id") Integer id) {
        System.out.println(bindingResult);
        if (bindingResult.hasErrors())
            return "redirect:/edit";

        stationeryService.update(id, stationery);
        return "redirect:/home";
    }

    @GetMapping("/delete")
    public String deletePage() {
        return "delete";
    }
    @PostMapping("/delete")
    public String deleteFormHandler( @RequestParam("id") Integer id ) {
        stationeryService.delete(id);
        return "redirect:/home";
    }

    @GetMapping("/show_criteria")
    public String criteriaPage() {
        return "criteria";
    }
    @PostMapping("/show_criteria")
    public String criteriaFormHandler( @RequestParam String manufacturer, ModelMap model ) {
        model.addAttribute("stationery", stationeryService.getByManufacturer(manufacturer));
        return "criteria_result";
    }

    @GetMapping("/register")
    public String register() {
        return "registration";
    }

    @PostMapping("/register")
    public String registerHandler(@RequestParam String username, @RequestParam String password) {
        try {
            boolean registerSuccess = userService.register(username, passwordEncoder.encode(password));
            if (registerSuccess)
                System.out.println("Создан пользователь " + username);
            else {
                System.out.println("Существует пользователь " + username);
                return "registration";
            }
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
        return "redirect:/auth";
    }

    @GetMapping("/auth")
    public String auth() {
        return "auth";
    }
}
