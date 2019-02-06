

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.border.Border;

/**
 *
 * @author mehmetsahin
 */
public class PlayTheGame extends JFrame {

    private JPanel panel;
    private JPanel headPanel;

    private JMenuBar menubar;

    private JMenu beeSweeper;
    private JMenuItem about;

    private JMenu settings;
    private JRadioButtonMenuItem easy;
    private JRadioButtonMenuItem medium;
    private JRadioButtonMenuItem hard;

    private JMenuItem help;

    //title panel
    private JPanel titlePanel;
    private ImageIcon titleIcon;
    private JLabel titleLabel;

    //restartpanel
    private JPanel restartPanel;
    private JButton restartButton;

    private Listener listener = new Listener();

    private BeeSweeper playMineSweeper;

    public PlayTheGame() {
        panel = new JPanel();
        headPanel = new JPanel();

        menubar = new JMenuBar();

        playMineSweeper = new BeeSweeper(600, 600);
        playMineSweeper.setPreferredSize(new Dimension(600, 600));

        //setSize(600, 900);
        setBackground(Color.white);
        setSize(600, 800);
        setResizable(true);
        Dimension dim = Toolkit.getDefaultToolkit().getScreenSize();
        this.setLocation(dim.width / 2 - this.getSize().width / 2, dim.height / 4 - this.getSize().height / 4 - 200);
        setVisible(true);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        createComponents();
        setJMenuBar(menubar);

        headPanel.setLayout(new BoxLayout(headPanel, BoxLayout.Y_AXIS));
        Border outer = BorderFactory.createEtchedBorder();
        Border inner = BorderFactory.createRaisedBevelBorder();
        Border compound = BorderFactory.createCompoundBorder(inner, outer);
        headPanel.setBorder(compound);
        panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));

        panel.add(headPanel);
        panel.add(playMineSweeper);
        add(panel);
        pack();
    }

    /**
     * Creates all the components of the frame
     */
    private void createComponents() {
        createAbout();
        createSetting();
        createHelp();
        createTitlePanel();
        restartPanel();
    }

    /**
     * Creates the About Menu
     */
    private void createAbout() {
        //create
        beeSweeper = new JMenu("Bee Weeper");
        about = new JMenuItem("About");

        about.addActionListener(listener);

        //add
        beeSweeper.add(about);
        menubar.add(beeSweeper);
    }

    /**
     * Creates the settings Menu with Radio Buttons
     */
    private void createSetting() {
        //create
        settings = new JMenu("Settings");

        easy = new JRadioButtonMenuItem("Easy", true);
        medium = new JRadioButtonMenuItem("Medium");
        hard = new JRadioButtonMenuItem("Hard");

        //add group
        ButtonGroup bG = new ButtonGroup();
        bG.add(easy);
        bG.add(medium);
        bG.add(hard);

        //action
        easy.addActionListener(listener);
        medium.addActionListener(listener);
        hard.addActionListener(listener);

        //add
        settings.add(easy);
        settings.add(medium);
        settings.add(hard);
        menubar.add(settings);

    }

    /**
     * Creates the Help Menu
     */
    private void createHelp() {
        //create
        help = new JMenuItem("Help");

        help.addActionListener(listener);

        //add
        menubar.add(help);
    }

    /**
     * Creates the title panel with the title image and label
     *
     */
    private void createTitlePanel() {
        //create
        titlePanel = new JPanel();
        titlePanel.setBackground(Color.WHITE);
        titleIcon = new ImageIcon("bee2.png");
        titleLabel = new JLabel(titleIcon);

        //action
        //add
        titlePanel.add(titleLabel);
        headPanel.add(titlePanel);
    }

    /**
     * Creates the restart button sets the size of the button and the Font style
     */
    private void restartPanel() {
        //create
        restartPanel = new JPanel();
        restartPanel.setBackground(Color.WHITE);
        restartButton = new JButton("Restart");
        restartButton.setFont(new Font("Serif", Font.PLAIN, 20));
        restartButton.setPreferredSize(new Dimension(400, 40));

        //action
        restartButton.addActionListener(listener);

        //add
        restartPanel.add(restartButton);
        headPanel.add(restartPanel);
    }

    private class Listener implements ActionListener {

        @Override
        public void actionPerformed(ActionEvent e) {
            if (easy.isSelected()) {
                playMineSweeper.setBeeNumber(20);
                playMineSweeper.startOver();
            } else if (medium.isSelected()) {
                playMineSweeper.setBeeNumber(35);
                playMineSweeper.startOver();
            } else if (hard.isSelected()) {
                playMineSweeper.setBeeNumber(50);
                playMineSweeper.startOver();
            } else {
                ;
            }
            if (e.getSource() == restartButton) {
                playMineSweeper.startOver();
            }
            if (e.getSource() == about) {
                JOptionPane.showMessageDialog(null, "BeeSweeper is a single-player puzzle video game. "
                        + "\nThe objective of the game is to clear a rectangular board containing "
                        + "\nhidden \"bees\" or bombs without detonating any of them, with help "
                        + "\nfrom clues about the number of neighboring mines in each field. "
                        + "\nThe game originates from the 1960s, and has been written for many computing "
                        + "\nplatforms in use today. It has many variations and offshoots. (took from Wikipedia)"
                        + "\n"
                        + "\nCreated BY @MEHMET SAHIN", "", JOptionPane.INFORMATION_MESSAGE);
            }
            if (e.getSource() == help) {
                JOptionPane.showMessageDialog(null, "Please check out Google for more information", "", JOptionPane.INFORMATION_MESSAGE);
            }
        }

    }

    public static void main(String[] args) {
        javax.swing.SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                new PlayTheGame();
            }
        });
    }
}
