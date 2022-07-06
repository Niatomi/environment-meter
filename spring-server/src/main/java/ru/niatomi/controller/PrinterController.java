package ru.niatomi.controller;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;

/**
 * @author niatomi
 */
@RequestMapping("/printer")
public interface PrinterController {

    @GetMapping("/csv")
    public void getDataCsv();

    @GetMapping("/excel")
    public void getDataExcel();

}
