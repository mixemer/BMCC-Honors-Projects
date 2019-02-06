
import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.Random;

public class BeeSweeper extends JPanel {

    private Cell[][] cells;

    private int w = 30;  // width and height of cell
    private int width; //width of the window
    private int height; //height of the window
    private int cols;
    private int rows;

    public static int beeNumber = 20; //number of bees in all cells

    private Image flag;

    private boolean gameOver = false;
    private boolean won = false;

    public BeeSweeper(int width, int height) {
        this.width = width;
        this.height = height;

        cols = this.width / w;
        rows = this.height / w;
        cells = new Cell[cols][rows];

        for (int i = 0; i < cols; i++) {
            for (int j = 0; j < rows; j++) {
                cells[i][j] = new Cell(i, j, w);
            }
        }

        seedBees();

        //sets how many bees around
        for (int i = 0; i < cols; i++) {
            for (int j = 0; j < rows; j++) {
                cells[i][j].setCountBees(countBees(i, j));
            }
        }

        setOpaque(true);
        addMouseListener(mouseAdapter);

    }

    /**
     * Generates a random number between low and high
     *
     * @param low an integer of lowest number
     * @param high an integer of highest number
     * @return a random number between low and high
     */
    private int randomNum(int low, int high) {
        Random random = new Random();

        return random.nextInt(high + 1 - low) + low;
    }

    /**
     * Seeds all the bees around the grid
     */
    private void seedBees() {
        for (int n = 0; n < this.beeNumber; n++) {
            int c = randomNum(0, cols - 1);
            int r = randomNum(0, rows - 1);

            if (!cells[c][r].isBee()) {
                cells[c][r].setBee(true);
            }
        }
    }

    /**
     * Counts how many bees around a neighboor cell
     *
     * @param c is the colum index
     * @param r is the row index
     * @return total number of bees in a neighboorhood
     */
    private int countBees(int c, int r) {
        int total = 0;

        for (int xoff = -1; xoff <= 1; xoff++) {
            for (int yoff = -1; yoff <= 1; yoff++) {
                int i = c + xoff;
                int j = r + yoff;
                if (i > -1 && i < cols && j > -1 && j < rows) {
                    if (cells[i][j].isBee()) {
                        total++;
                    }
                }
            }
        }
        return total;
    }

    /**
     * Finds all the zeros around neighboors and reveals them to public
     *
     * @param c is the column index
     * @param r is the row index
     */
    private void zerosReveal(int c, int r) {
        for (int xoff = -1; xoff <= 1; xoff++) {
            for (int yoff = -1; yoff <= 1; yoff++) {
                int i = c + xoff;
                int j = r + yoff;
                if (i > -1 && i < cols && j > -1 && j < rows) {
                    if (!cells[i][j].isBee() && !cells[i][j].isRevealed()) {
                        cells[i][j].setRevealed(true);
                        if (cells[i][j].getCountBees() == 0) {
                            zerosReveal(i, j);
                        }
                    }
                }
            }
        }
    }

    /**
     * Once user steps over a bee, game is over by reaveling all cells
     */
    private void gameOver() {
        for (int i = 0; i < cols; i++) {
            for (int j = 0; j < rows; j++) {
                cells[i][j].setRevealed(true);
            }
        }
    }

    /**
     * Starts the game over
     */
    public void startOver() {
        for (int i = 0; i < cols; i++) {
            for (int j = 0; j < rows; j++) {
                cells[i][j].setRevealed(false);
                cells[i][j].setBee(false);
                cells[i][j].setCountBees(0);
                cells[i][j].setFlagged(false);
                won = false;
                gameOver = false;
            }
        }

        seedBees();

        //sets how many bees around by coling setCountBees method
        for (int i = 0; i < cols; i++) {
            for (int j = 0; j < rows; j++) {
                cells[i][j].setCountBees(countBees(i, j));
            }
        }
        repaint();
    }

    /**
     * For mouse
     */
    private MouseAdapter mouseAdapter;

    {
        mouseAdapter = new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent me) {

                if (SwingUtilities.isLeftMouseButton(me)) {
                    int x = me.getX();
                    int y = me.getY();

                    for (int i = 0; i < cols; i++) {
                        for (int j = 0; j < rows; j++) {
                            if (cells[i][j].isLocation(x, y) && !cells[i][j].isRevealed() && !cells[i][j].isFlagged()) {
                                cells[i][j].setRevealed(true);
                                if (cells[i][j].isBee()) {
                                    gameOver = true;
                                    gameOver();
                                }

                                if (cells[i][j].getCountBees() == 0) {
                                    zerosReveal(i, j); //recursion
                                }

                            }
                        }
                    }
                }
                //this is for the flagging and unflagging
                if (SwingUtilities.isRightMouseButton(me)) {
                    int x = me.getX();
                    int y = me.getY();
                    for (int i = 0; i < cols; i++) {
                        for (int j = 0; j < rows; j++) {
                            if (cells[i][j].isLocation(x, y) && !cells[i][j].isRevealed() && !cells[i][j].isFlagged()) {
                                cells[i][j].setFlagged(true);
                            } else if (cells[i][j].isLocation(x, y) && cells[i][j].isFlagged()) {
                                cells[i][j].setFlagged(false);
                            }
                        }
                    }
                }

                repaint();
            }
        };
    }

    /**
     * Gets the number of bees on the grid
     *
     * @return number of bees on the grid
     */
    public int getBeeNumber() {
        return beeNumber;
    }

    /**
     * Sets the number of bees on the grid
     *
     * @param beeNumber an integer for bee number
     */
    public void setBeeNumber(int beeNumber) {
        this.beeNumber = beeNumber;
    }

    /**
     * When all the bees are found, the user winds
     *
     * @return true if all the bees are revealed
     */
    private boolean won() {
        for (int i = 0; i < cols; i++) {
            for (int j = 0; j < rows; j++) {
                if (!cells[i][j].isRevealed() && !cells[i][j].isBee()) {
                    return false;
                }
            }
        }
        won = true;
        return true;
    }

    public void paint(Graphics g) {

        //flag icon
        ImageIcon i1 = new ImageIcon("flag.png");
        flag = i1.getImage();

        // draws the cells
        for (int i = 0; i < cols; i++) {
            for (int j = 0; j < rows; j++) {
                g.setColor(Color.green);
                g.fill3DRect(cells[i][j].getI() * w, cells[i][j].getJ() * w, w, w, true);
            }
        }

        for (int i = 0; i < cols; i++) {
            for (int j = 0; j < rows; j++) {
                if (cells[i][j].isRevealed() && !cells[i][j].isFlagged()) {
                    if (cells[i][j].isBee()) { // if it is a bee
                        g.setColor(Color.gray);
                        g.fill3DRect(i * w, j * w, w, w, false);

                        g.setColor(Color.red);
                        g.fillOval(i * w + 5, j * w + 5, w - 10, w - 10);

                        g.setColor(Color.BLACK);
                        g.setFont(new Font("arial", Font.ITALIC, 70));
                        g.drawString("Game Over", 100, height / 2);

                        g.setFont(new Font("arial", Font.ITALIC, 40));
                        g.drawString("Click restart to start!", 120, height / 2 + 30);

                    } else { // if it is a number
                        if (cells[i][j].getCountBees() == 0) {
                            g.setColor(Color.gray);
                            g.fill3DRect(i * w, j * w, w, w, false);
                        } else {
                            g.setColor(Color.gray);
                            g.fill3DRect(i * w, j * w, w, w, false);

                            g.setColor(Color.yellow);
                            g.setFont(new Font("arial", Font.ITALIC, 20));
                            g.drawString(Integer.toString(cells[i][j].getCountBees()), i * w + 10, j * w + 20);
                        }
                    }
                } else {
                    if (cells[i][j].isFlagged()) { //flag image
                        g.drawImage(flag, i * w, j * w, w, w, null);
                    }
                }
            }
        }

        /**
         * This print "You win" string when the user wins if the user has not
         * lost the game
         */
        if (won() && !gameOver) {
            String won = "You-Won!!!";
            for (int i = 0; i < won.length(); i++) {
                int r = randomNum(50, 255);
                int ge = randomNum(50, 255);
                int y = randomNum(50, 255);
                g.setColor(new Color(r, ge, y));
                g.setFont(new Font("arial", Font.ITALIC, 70));
                g.drawString(String.valueOf(won.charAt(i)), 100 + (i * 40), height / 2);
                repaint();
            }

            g.setFont(new Font("arial", Font.ITALIC, 40));
            g.drawString("Click restart to start!", 120, height / 2 + 30);
        }
    }
}
