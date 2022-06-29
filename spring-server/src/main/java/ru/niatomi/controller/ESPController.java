package ru.niatomi.controller;

import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import ru.niatomi.model.dto.ReferenceDataDto;
import ru.niatomi.model.dto.SensorsDto;
import ru.niatomi.model.dto.TimeScheduleDto;

import java.util.List;

/**
 * @author niatomi
 */
@Controller
@RequestMapping("/esp")
public interface ESPController {

    @GetMapping("/getReferenceData")
    public ResponseEntity<ReferenceDataDto> getReferenceData();

    @GetMapping("/getTimeSchedule")
    public ResponseEntity<List<TimeScheduleDto>> getTimeSchedule();

    @PostMapping("/sendSensorsData")
    public void getTimeSchedule (
            @RequestBody SensorsDto sensorsDto
            );

}
