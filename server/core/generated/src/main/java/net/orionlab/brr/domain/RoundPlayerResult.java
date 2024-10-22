// license-header java merge-point
//
// Attention: Generated code! Do not modify by hand!
// Generated by: hibernate/HibernateEntity.vsl in andromda-hibernate-cartridge.
//
package net.orionlab.brr.domain;

import java.io.Serializable;
import java.util.Date;

/**
 * 
 */
// HibernateEntity.vsl annotations merge-point
public abstract class RoundPlayerResult
    implements Serializable, Comparable<RoundPlayerResult>
{
    /**
     * The serial version UID of this class. Needed for serialization.
     */
    private static final long serialVersionUID = -4961238355259895154L;

    // Generate 8 attributes
    private KillReasonType killReason;

    /**
     * 
     * @return this.killReason KillReasonType
     */
    public KillReasonType getKillReason()
    {
        return this.killReason;
    }

    /**
     * 
     * @param killReasonIn KillReasonType
     */
    public void setKillReason(KillReasonType killReasonIn)
    {
        this.killReason = killReasonIn;
    }

    private Integer position;

    /**
     * 
     * @return this.position Integer
     */
    public Integer getPosition()
    {
        return this.position;
    }

    /**
     * 
     * @param positionIn Integer
     */
    public void setPosition(Integer positionIn)
    {
        this.position = positionIn;
    }

    private Integer killedPosition;

    /**
     * 
     * @return this.killedPosition Integer
     */
    public Integer getKilledPosition()
    {
        return this.killedPosition;
    }

    /**
     * 
     * @param killedPositionIn Integer
     */
    public void setKilledPosition(Integer killedPositionIn)
    {
        this.killedPosition = killedPositionIn;
    }

    private Long winAmount;

    /**
     * 
     * @return this.winAmount Long
     */
    public Long getWinAmount()
    {
        return this.winAmount;
    }

    /**
     * 
     * @param winAmountIn Long
     */
    public void setWinAmount(Long winAmountIn)
    {
        this.winAmount = winAmountIn;
    }

    private Date dateCreate;

    /**
     * 
     * @return this.dateCreate Date
     */
    public Date getDateCreate()
    {
        return this.dateCreate;
    }

    /**
     * 
     * @param dateCreateIn Date
     */
    public void setDateCreate(Date dateCreateIn)
    {
        this.dateCreate = dateCreateIn;
    }

    private Date dateEdit;

    /**
     * 
     * @return this.dateEdit Date
     */
    public Date getDateEdit()
    {
        return this.dateEdit;
    }

    /**
     * 
     * @param dateEditIn Date
     */
    public void setDateEdit(Date dateEditIn)
    {
        this.dateEdit = dateEditIn;
    }

    private Boolean isArchived = Boolean.valueOf(false);

    /**
     * 
     * @return this.isArchived Boolean
     */
    public Boolean getIsArchived()
    {
        return this.isArchived;
    }

    /**
     * 
     * @param isArchivedIn Boolean
     */
    public void setIsArchived(Boolean isArchivedIn)
    {
        this.isArchived = isArchivedIn;
    }

    private Long id;

    /**
     * 
     * @return this.id Long
     */
    public Long getId()
    {
        return this.id;
    }

    /**
     * 
     * @param idIn Long
     */
    public void setId(Long idIn)
    {
        this.id = idIn;
    }

    // Generate 3 associations
    private RoomRound round;

    /**
     * 
     * @return this.round RoomRound
     */
    public RoomRound getRound()
    {
        return this.round;
    }

    /**
     * 
     * @param roundIn RoomRound
     */
    public void setRound(RoomRound roundIn)
    {
        this.round = roundIn;
    }

    private Player player;

    /**
     * 
     * @return this.player Player
     */
    public Player getPlayer()
    {
        return this.player;
    }

    /**
     * 
     * @param playerIn Player
     */
    public void setPlayer(Player playerIn)
    {
        this.player = playerIn;
    }

    private Player killedPlayer;

    /**
     * 
     * @return this.killedPlayer Player
     */
    public Player getKilledPlayer()
    {
        return this.killedPlayer;
    }

    /**
     * 
     * @param killedPlayerIn Player
     */
    public void setKilledPlayer(Player killedPlayerIn)
    {
        this.killedPlayer = killedPlayerIn;
    }

    /**
     * Returns <code>true</code> if the argument is an RoundPlayerResult instance and all identifiers for this entity
     * equal the identifiers of the argument entity. Returns <code>false</code> otherwise.
     */
    @Override
    public boolean equals(Object object)
    {
        if (this == object)
        {
            return true;
        }
        if (!(object instanceof RoundPlayerResult))
        {
            return false;
        }
        final RoundPlayerResult that = (RoundPlayerResult)object;
        if (this.id == null || that.getId() == null || !this.id.equals(that.getId()))
        {
            return false;
        }
        return true;
    }

    /**
     * Returns a hash code based on this entity's identifiers.
     */
    @Override
    public int hashCode()
    {
        int hashCode = 0;
        hashCode = 29 * hashCode + (this.id == null ? 0 : this.id.hashCode());

        return hashCode;
    }

    /**
     * Constructs new instances of {@link RoundPlayerResult}.
     */
    public static final class Factory
    {
        /**
         * Constructs a new instance of {@link RoundPlayerResult}.
         * @return new RoundPlayerResultImpl()
         */
        public static RoundPlayerResult newInstance()
        {
            return new RoundPlayerResultImpl();
        }

        /**
         * Constructs a new instance of {@link RoundPlayerResult}, taking all required and/or
         * read-only properties as arguments, except for identifiers.
         * @param killReason KillReasonType
         * @param dateCreate Date
         * @param round RoomRound
         * @param player Player
         * @return newInstance
         */
        public static RoundPlayerResult newInstance(KillReasonType killReason, Date dateCreate, RoomRound round, Player player)
        {
            final RoundPlayerResult entity = new RoundPlayerResultImpl();
            entity.setKillReason(killReason);
            entity.setDateCreate(dateCreate);
            entity.setRound(round);
            entity.setPlayer(player);
            return entity;
        }

        /**
         * Constructs a new instance of {@link RoundPlayerResult}, taking all possible properties
         * (except the identifier(s))as arguments.
         * @param killReason KillReasonType
         * @param position Integer
         * @param killedPosition Integer
         * @param winAmount Long
         * @param dateCreate Date
         * @param dateEdit Date
         * @param isArchived Boolean
         * @param round RoomRound
         * @param player Player
         * @param killedPlayer Player
         * @return newInstance RoundPlayerResult
         */
        public static RoundPlayerResult newInstance(KillReasonType killReason, Integer position, Integer killedPosition, Long winAmount, Date dateCreate, Date dateEdit, Boolean isArchived, RoomRound round, Player player, Player killedPlayer)
        {
            final RoundPlayerResult entity = new RoundPlayerResultImpl();
            entity.setKillReason(killReason);
            entity.setPosition(position);
            entity.setKilledPosition(killedPosition);
            entity.setWinAmount(winAmount);
            entity.setDateCreate(dateCreate);
            entity.setDateEdit(dateEdit);
            entity.setIsArchived(isArchived);
            entity.setRound(round);
            entity.setPlayer(player);
            entity.setKilledPlayer(killedPlayer);
            return entity;
        }
    }

    /**
     * @see Comparable#compareTo
     */
    public int compareTo(RoundPlayerResult o)
    {
        int cmp = 0;
        if (this.getId() != null)
        {
            cmp = this.getId().compareTo(o.getId());
        }
        else
        {
            if (this.getKillReason() != null)
            {
                cmp = (cmp != 0 ? cmp : this.getKillReason().compareTo(o.getKillReason()));
            }
            if (this.getPosition() != null)
            {
                cmp = (cmp != 0 ? cmp : this.getPosition().compareTo(o.getPosition()));
            }
            if (this.getKilledPosition() != null)
            {
                cmp = (cmp != 0 ? cmp : this.getKilledPosition().compareTo(o.getKilledPosition()));
            }
            if (this.getWinAmount() != null)
            {
                cmp = (cmp != 0 ? cmp : this.getWinAmount().compareTo(o.getWinAmount()));
            }
            if (this.getDateCreate() != null)
            {
                cmp = (cmp != 0 ? cmp : this.getDateCreate().compareTo(o.getDateCreate()));
            }
            if (this.getDateEdit() != null)
            {
                cmp = (cmp != 0 ? cmp : this.getDateEdit().compareTo(o.getDateEdit()));
            }
            if (this.getIsArchived() != null)
            {
                cmp = (cmp != 0 ? cmp : this.getIsArchived().compareTo(o.getIsArchived()));
            }
        }
        return cmp;
    }
// HibernateEntity.vsl merge-point
}