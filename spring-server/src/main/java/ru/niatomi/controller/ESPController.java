package ru.niatomi.controller;

import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import ru.niatomi.model.dto.configFiles.ReferenceDataDto;
import ru.niatomi.model.dto.configFiles.SensorsDto;
import ru.niatomi.model.dto.time.TimeScheduleDto;
import ru.niatomi.model.dto.configFiles.UpdatableDto;

/**
 * @author niatomi
 */
@Controller
@RequestMapping("/esp")
public interface ESPController {

    @GetMapping("/getReferenceData")
    public ResponseEntity<ReferenceDataDto> getReferenceData();

    @GetMapping("/getTimeSchedule")
    public ResponseEntity<TimeScheduleDto> getTimeSchedule();

    @PostMapping("/sendSensorsData")
    public ResponseEntity<String> saveSensorData (
            @RequestBody SensorsDto sensorsDto
            );

    @GetMapping("/checkOnReferenceUpdate")
    public ResponseEntity<UpdatableDto> checkOnReferenceUpdate();

    @PostMapping("/stateReferenceUpdateState")
    public void stateReferenceUpdate();

    @GetMapping("/checkOnTimeReferenceUpdate")
    public ResponseEntity<UpdatableDto> checkOnTimeReferenceUpdate();

    @PostMapping("/stateTimeReferenceUpdate")
    public void stateTimeReferenceUpdate();

}
