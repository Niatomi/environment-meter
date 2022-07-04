package ru.niatomi.controller.Impl;

import lombok.AllArgsConstructor;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.RestController;
import ru.niatomi.controller.ESPController;
import ru.niatomi.model.dto.configFiles.ReferenceDataDto;
import ru.niatomi.model.dto.configFiles.SensorsDto;
import ru.niatomi.model.dto.time.TimeScheduleDto;
import ru.niatomi.model.dto.configFiles.UpdatableDto;
import ru.niatomi.service.ESPService;

/**
 * @author niatomi
 */
@RestController
@AllArgsConstructor
public class ESPControllerImpl implements ESPController {

    private final ESPService espService ;

    @Override
    public ResponseEntity<ReferenceDataDto> getReferenceData() {
        return ResponseEntity.ok(espService.getReferenceData());
    }

    @Override
    public ResponseEntity<TimeScheduleDto> getTimeSchedule() {
        return ResponseEntity.ok(espService.getTimeSchedule());
    }

    @Override
    public void saveSensorData(SensorsDto sensorsDto) {
        espService.saveSensorData(sensorsDto);
    }

    @Override
    public ResponseEntity<UpdatableDto> checkOnReferenceUpdate() {
        return ResponseEntity.ok(espService.checkOnReferenceUpdate());
    }

    @Override
    public void stateReferenceUpdate() {
        espService.stateReferenceUpdate();
    }

    @Override
    public ResponseEntity<UpdatableDto> checkOnTimeReferenceUpdate() {
        return null;
    }

    @Override
    public void stateTimeReferenceUpdate() {

    }
}
