<GameFile>
  <PropertyGroup Name="MainScene" Type="Scene" ID="a2ee0952-26b5-49ae-8bf9-4f1d6279b798" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="55" Speed="1.0000" ActivedAnimationName="titleAnimation">
        <Timeline ActionTag="283241320" Property="Position">
          <PointFrame FrameIndex="1" X="480.0000" Y="896.0000">
            <EasingData Type="5" />
          </PointFrame>
          <PointFrame FrameIndex="50" X="480.0001" Y="320.1478">
            <EasingData Type="5" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="283241320" Property="VisibleForFrame">
          <BoolFrame FrameIndex="55" Tween="False" Value="True" />
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="titleAnimation" StartIndex="1" EndIndex="55">
          <RenderColor A="255" R="210" G="180" B="140" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Scene" ctype="GameNodeObjectData">
        <Size X="960.0000" Y="640.0000" />
        <Children>
          <AbstractNodeData Name="background" ActionTag="-746874720" Tag="91" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" ctype="SpriteObjectData">
            <Size X="960.0000" Y="640.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="480.0000" Y="320.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="0.5000" />
            <PreSize X="1.0000" Y="1.0000" />
            <FileData Type="Normal" Path="assets/black-1072366_960_720.jpg" Plist="" />
            <BlendFunc Src="770" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="ScorePanel" ActionTag="1751422407" VisibleForFrame="False" Tag="3" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" PercentWidthEnable="True" PercentHeightEnable="True" PercentWidthEnabled="True" PercentHeightEnabled="True" LeftMargin="96.0000" RightMargin="384.0000" TopMargin="12.8000" BottomMargin="563.2000" TouchEnable="True" ClipAble="False" BackColorAlpha="0" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
            <Size X="480.0000" Y="64.0000" />
            <Children>
              <AbstractNodeData Name="ScoreLabel" ActionTag="-1678326980" Tag="4" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" RightMargin="337.0000" TopMargin="7.0000" BottomMargin="7.0000" FontSize="36" LabelText="SCORE:" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                <Size X="143.0000" Y="50.0000" />
                <AnchorPoint ScaleY="0.5000" />
                <Position Y="32.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition Y="0.5000" />
                <PreSize X="0.2979" Y="0.7813" />
                <FontResource Type="Normal" Path="assets/space_invaders.ttf" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="ScorePointLabel" ActionTag="-1256334787" Tag="5" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="238.8960" RightMargin="134.1040" TopMargin="7.0000" BottomMargin="7.0000" FontSize="36" LabelText="0000" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                <Size X="107.0000" Y="50.0000" />
                <AnchorPoint ScaleY="0.5000" />
                <Position X="238.8960" Y="32.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.4977" Y="0.5000" />
                <PreSize X="0.2229" Y="0.7813" />
                <FontResource Type="Normal" Path="assets/space_invaders.ttf" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleY="0.5000" />
            <Position X="96.0000" Y="595.2000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.1000" Y="0.9300" />
            <PreSize X="0.5000" Y="0.1000" />
            <SingleColor A="255" R="0" G="0" B="0" />
            <FirstColor A="255" R="150" G="200" B="255" />
            <EndColor A="255" R="255" G="255" B="255" />
            <ColorVector ScaleY="1.0000" />
          </AbstractNodeData>
          <AbstractNodeData Name="titleLabel" ActionTag="283241320" Tag="104" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="159.0001" RightMargin="158.9999" TopMargin="220.8522" BottomMargin="221.1478" FontSize="72" LabelText="SPACE INVADER&#xA;TAP TO START" HorizontalAlignmentType="HT_Center" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
            <Size X="642.0000" Y="198.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="480.0001" Y="320.1478" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="0" G="255" B="13" />
            <PrePosition X="0.5000" Y="0.5002" />
            <PreSize X="0.6687" Y="0.3094" />
            <FontResource Type="Normal" Path="assets/space_invaders.ttf" Plist="" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="gameStateLabel" ActionTag="1799354862" VisibleForFrame="False" Tag="142" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="257.5000" RightMargin="257.5000" TopMargin="269.5000" BottomMargin="269.5000" FontSize="72" LabelText="GAME OVER" HorizontalAlignmentType="HT_Center" OutlineEnabled="True" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
            <Size X="445.0000" Y="101.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="480.0000" Y="320.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="0.5000" />
            <PreSize X="0.4635" Y="0.1578" />
            <FontResource Type="Normal" Path="assets/space_invaders.ttf" Plist="" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>