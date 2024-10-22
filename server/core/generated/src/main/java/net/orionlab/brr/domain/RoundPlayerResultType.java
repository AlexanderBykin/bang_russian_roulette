// license-header java merge-point
//
// Attention: Generated code! Do not modify by hand!
// Generated by: TypeSafeEnumeration.vsl in andromda-java-cartridge.
// Model Class:  AndroMDAModel::net.orionlab.brr::domain::RoundPlayerResultType
// Metafacade:   org.andromda.metafacades.uml.Enumeration
// Stereotype:  Enumeration
//
package net.orionlab.brr.domain;

import java.util.ArrayList;
import java.util.Collections;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;

/**
 * 
 */
public enum RoundPlayerResultType
{
    /** TODO: Model Documentation for Enumeration Literal LOSE value "LOSE" */
    LOSE("LOSE"),
    /** TODO: Model Documentation for Enumeration Literal WIN value "WIN" */
    WIN("WIN");

    /**
     * The serial version UID of this class. Needed for serialization.
     */
    private static final long serialVersionUID = -6908407526917033532L;

    private final String enumValue;

    /**
     * The constructor with enumeration literal value allowing
     * super classes to access it.
     */
    private RoundPlayerResultType(String value)
    {
        this.enumValue = value;
    }

    /*
     * Do not override this method directly. Use an alternate name
     * if providing a different toString implementation
     * @see Object#toString()
    @Override
    public String toString()
    {
        return String.valueOf(this.enumValue);
    }
     */

    /**
     * Retrieves an instance of RoundPlayerResultType from <code>its name</code>.
     *
     * @param name the name to create the RoundPlayerResultType from.
     * @return The enumeration literal named after the 'name' argument
     */
    public static RoundPlayerResultType fromString(String name)
    {
        return RoundPlayerResultType.valueOf(name);
    }

    /**
     * Returns an enumeration literal String <code>value</code>.
     * Required by JAXB2 enumeration implementation
     *
     * @return String with corresponding value
     */
    public String value()
    {
        return this.enumValue;
    }

    /**
     * Returns an instance of RoundPlayerResultType from String <code>value</code>.
     * Required by JAXB2 enumeration implementation
     *
     * @param value the value to create the RoundPlayerResultType from.
     * @return static Enumeration with corresponding value
     */
    public static RoundPlayerResultType fromValue(String value)
    {
        for (RoundPlayerResultType enumName: RoundPlayerResultType.values())
        {
            if (enumName.getValue().equals(value))
            {
                return enumName;
            }
        }
        throw new IllegalArgumentException("RoundPlayerResultType.fromValue(" + value + ')');
    }

    /**
     * Gets the underlying value of this type safe enumeration.
     * This method is necessary to comply with DaoBase implementation.
     * @return The name of this literal.
     */
    public String getValue()
    {
        return this.enumValue;
    }

    /**
     * Returns an unmodifiable list containing the literals that are known by this enumeration.
     *
     * @return A List containing the actual literals defined by this enumeration, this list
     *         can not be modified.
     */
    public static List<String> literals()
    {
        return RoundPlayerResultType.literals;
    }

    /**
     * Returns an unmodifiable list containing the names of the literals that are known
     * by this enumeration.
     *
     * @return A List containing the actual names of the literals defined by this
     *         enumeration, this list can not be modified.
     */
    public static List<String> names()
    {
        return RoundPlayerResultType.names;
    }

    private static Map<String, RoundPlayerResultType> values = new LinkedHashMap<String, RoundPlayerResultType>(2, 1);
    private static List<String> literals = new ArrayList<String>(2);
    private static List<String> names = new ArrayList<String>(2);
    private static List<RoundPlayerResultType> valueList = new ArrayList<RoundPlayerResultType>(2);

    /**
     * Initializes the values.
     */
    static
    {
        synchronized (RoundPlayerResultType.values)
        {
            RoundPlayerResultType.values.put(LOSE.enumValue, LOSE);
            RoundPlayerResultType.values.put(WIN.enumValue, WIN);
        }
        synchronized (RoundPlayerResultType.valueList)
        {
            RoundPlayerResultType.valueList.add(LOSE);
            RoundPlayerResultType.valueList.add(WIN);
            RoundPlayerResultType.valueList = Collections.unmodifiableList(valueList);
        }
        synchronized (RoundPlayerResultType.literals)
        {
            RoundPlayerResultType.literals.add(LOSE.enumValue);
            RoundPlayerResultType.literals.add(WIN.enumValue);
            RoundPlayerResultType.literals = Collections.unmodifiableList(literals);
        }
        synchronized (RoundPlayerResultType.names)
        {
            RoundPlayerResultType.names.add("LOSE");
            RoundPlayerResultType.names.add("WIN");
            RoundPlayerResultType.names = Collections.unmodifiableList(names);
        }
    }
    // type-safe-enumeration-object java merge-point
}