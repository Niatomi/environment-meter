package ru.niatomi.model.domain.validation;

import ru.niatomi.model.domain.validation.validatior.I2CCheckTimeRestrictionsValidator;

import javax.validation.Constraint;
import javax.validation.Payload;
import java.lang.annotation.*;

/**
 * @author niatomi
 */
@Documented
//@Constraint(validatedBy = I2CCheckTimeRestrictionsValidator.class)
@Target( { ElementType.METHOD, ElementType.FIELD })
@Retention(RetentionPolicy.RUNTIME)
public @interface I2CCheckTimeRestrictions {

    String message() default "Arduino не может так быстро снимать значения с датчиков";
    Class<?>[] groups() default {};
    Class<? extends Payload>[] payload() default {};

}
