
class Cell {

    private int w;  // width and height of cell

    private int i;  //i * w = x(location)  // index of column
    private int j;  //j * w = y(location)  // index of raw

    private boolean bee;  // a cirlcle inside an ractengle
    private int countBees;

    private boolean revealed = false;

    private boolean flagged;

    public Cell(int i, int j, int w) {

        this.i = i;
        this.j = j;
        this.w = w;

    }

    /**
     * Sets the cell as flagged
     *
     * @param flagged true or false
     */
    public void setFlagged(boolean flagged) {
        this.flagged = flagged;
    }

    /**
     * Checks if the cell is flagged or not
     *
     * @return
     */
    public boolean isFlagged() {
        return this.flagged;
    }

    /**
     * index of the cell
     *
     * @return index of the cell
     */
    public int getI() {
        return i;
    }

    /**
     * index of the cell
     *
     * @return index of the cell
     */
    public int getJ() {
        return j;
    }

    /**
     * Puts a bee in a cell
     *
     * @param bee a boolean for setting a bee
     */
    public void setBee(boolean bee) {
        this.bee = bee;
    }

    /**
     * Checks if there is a bee inside a cell
     *
     * @return true or false based on if there is a bee inside the cell
     */
    public boolean isBee() {
        return bee;
    }

    /**
     * Check if a cell is been revealed
     *
     * @return true or false based on if there a cell is been revealed
     */
    public boolean isRevealed() {
        return revealed;
    }

    /**
     * Reveals or unreveals a cell
     *
     * @param revealed a boolean for revealing
     */
    public void setRevealed(boolean revealed) {
        this.revealed = revealed;
    }

    /**
     * Count of the bee around this cell
     *
     * @return how many bees around this cell
     */
    public int getCountBees() {
        return countBees;
    }

    /**
     * Sets the bee count around this cell
     *
     * @param countBees
     */
    public void setCountBees(int countBees) {
        this.countBees = countBees;
    }

    // for the mouse!!
    /**
     * Check if mouse clicked is inside this cell.
     *
     * @param x location of mouse x
     * @param y location of mouse y
     * @return true if mouse is inside this cell otherwise false
     */
    public boolean isLocation(int x, int y) {
        return (x > (this.i * w) && x < (this.i * w) + this.w && y > (this.j * w) && y < (this.j * w) + this.w);
    }
}
